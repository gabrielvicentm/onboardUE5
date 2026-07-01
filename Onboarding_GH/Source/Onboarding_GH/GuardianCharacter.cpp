#include "GuardianCharacter.h" // esse include é o do .h da classe,(que é o arquivo que define a classe que eu implemento nesse arquivo .cpp)

#include "Camera/CameraComponent.h" // esse include é o do componente da câmera, que eu uso pra criar a câmera e tamém para usar as funções de ACharacter que herdam dessa classe
#include "Components/CapsuleComponent.h" // esse include é o do componente da capsula(colisão) do personagem, eu uso para criar a capsula/colisão
#include "EnhancedInputComponent.h" //include do componente de input melhorado, que eu uso para bindar as ações de input do personagem  
#include "EnhancedInputSubsystems.h" //include dos subsistemas de input melhorado, que eu uso para adicionar o input do personagem
#include "GameFramework/CharacterMovementComponent.h" //include do componente de movimentação do personagem, que eu uso para definir a velocidade de movimentação do personagem
#include "GameFramework/SpringArmComponent.h"//include do componente do braço da câmera, que eu uso para criar o braço da câmera( o sring arm component)

AGuardianCharacter::AGuardianCharacter()
{
    //aqui ele tá desabilitando o tick do personagem, ou seja ele não vai chamar o personagem a cada frame
    //isso é bem comum, a maioria das funções c++ não precisam de tick, pq devem não devem ser chamadas a cada frame
    PrimaryActorTick.bCanEverTick = false;

    //aqui está definindo o tamanho da capsula(colisão) do personagem, 42 é o raio e 96 é a altura
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

    //essas 3 linhas aqui desabilitam a rotação do personagem ligada a câmera, ou seja a movimentação indepede da câmera
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    //aqui eu estou pegando o componente de movimentação do personagem, e defino que ele vai rotacionar o personagem de acordo com a direção que ele está se movendo
    GetCharacterMovement()->bOrientRotationToMovement = true;
    //aqui eu decido a velocidade de rotação dele, somente no eixo Y
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
    //e aqui eu defino a velocidade maxima de movimentação que é a velocidade de caminhada
    //esses valores foram definidos no .h da classe
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

    //Aqui eu crio o componente do'braço' da câmera que vai segui-la
    //OBS: O USpringArmComponent(braço da câmera vai seguir o personagem, e vai manter a câmera a uma distância definida, e ele vai rotacionar a câmera de acordo com a rotação do personagem
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 500.0f;
    CameraBoom->bUsePawnControlRotation = true;

    //Aqui eu crio o componente da câmera seguindo o braço da câmera
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;
}

//aqui é definido oq vai acontecer quando o jogo iniciar,
//nesse caso ele vai setar a velocidade de mov do personagem e vai adicionar o input do personagem, que é definido no .h da classe
void AGuardianCharacter::BeginPlay()
{
    //esse Super aqui serve para chamar a função BeginPlay da classe pai, que é a ACharacter, que é a classe que o AGuardianCharacter herda
    Super::BeginPlay();

    //aqui eu defino a vel de mov do personagem que é walkspeed
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

    //aqui eu verifico se o player controller é valido,
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        //agora eu verifico se o local player é valido 
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                //aqui eu adiciono o input do personagem que é definido no .h da classe é o 'DefaultMappingContext'
                //esse DefaultMappingContext é um objeto que define quais ações de input estão disponíveis para o personagem, e quais teclas ou botões estão associados a essas ações
                if (DefaultMappingContext)
                {
                    Subsystem->AddMappingContext(DefaultMappingContext, 0);
                }
            }
        }
    }

    //aqui é definido oq acontece quando o jogador apertar os bot~eos de movimentação, ataque esquiva e interação que foram definidos no .h da classe
void AGuardianCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    //mesma ideia do outro super, chama a função pai da classe que é a ACharacter
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //verifico se PlayerInputComponent é válido, faço um cast para UEnhancedInputComponent, que é a classe que vai me permitir bindar as ações de input do personagem
    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    //verifico se EnhancedInputComponent é válido, se não for válido eu retorno, pq não tem como bindar as ações de input do personagem
    if (!EnhancedInputComponent)
    {
        return;
    }
//aqui eu verifico se a ação foi de movimentação, se for, eu chamo a função Move(linha 112)
    if (MoveAction)
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGuardianCharacter::Move);
    }
//verifico se a ação foi olhar, se for eu chamo a func Look(linha 130)
    if (LookAction)
    {
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGuardianCharacter::Look);
    }
//verifico se o input/ação foi de atacar, se for chama a func Attack
    if (AttackAction)
    {
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AGuardianCharacter::Attack);
    }

    //verifico se o input/ação foi de esquivar, se for chama a func Dodge
    if (DodgeAction)
    {
        EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &AGuardianCharacter::Dodge);
    }

    //verifico se o input/ação foi de interagir, se for chama a func Interact
    if (InteractAction)
    {
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGuardianCharacter::Interact);
    }
}

//finalmente a função Move, ela pega o valor do input de movimentação do jogador, que é um vetor 2D,
//e transforma esse vetor2D em um vetor 3D, que é a idreação que o personagem vai se mover,
void AGuardianCharacter::Move(const FInputActionValue& Value)
{
    //aqui pega o vetor2D e passa ele para variavel MovementVector, que vai ser usado para definir a direção do movimento do personagem
    const FVector2D MovementVector = Value.Get<FVector2D>();

    //se o controller não for válido, eu retorno, pq não tem como mover o personagem sem um controller
    if (!Controller)
    {
        return;
    }

    //essa ControlRotation é a rotação do controller, que por sua vez é a rotação da câmera,
    const FRotator ControlRotation = Controller->GetControlRotation();
    //aqui eu pego a rotação do controller e crio uma nova rotação, que é a rotação do personagem, mas só no eixo Y
    const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);

    //agora nesses FVector ForwardDirection e RightDirection eu pego e transformo a rotação do personagem num vetor3D
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    //ai finalment eu uso a função AddMovementInput(que é uma função da classe ACharacter) para adicionar o input de de movimejntação do personagem
    //para essa função eu passo a direação e o valor da movimentação, que é o vetor2D que eu peguei no começo da função
    AddMovementInput(ForwardDirection, MovementVector.Y);
    AddMovementInput(RightDirection, MovementVector.X);
}

//função de olhar, pega o movimento 2d do mouse, e transforma em movimento de rotação de câmera
void AGuardianCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookAxisVector = Value.Get<FVector2D>();

    //ai aqui nas funções AddControllerYawInput e AddControllerPitchInput(que são da classe ACharacter) 
   //eu passo o valor do vetor2D que eu peguei no começo da função, para rotacionar a câmera do personagem
    AddControllerYawInput(LookAxisVector.X); 
    AddControllerPitchInput(LookAxisVector.Y);
}

//aqui é uma gambiarrinha que quando apertar o botão de ataque, vai tocar a anim,ação de ataque e aparecer um LOG na tela

void AGuardianCharacter::Attack()
{
    UE_LOG(LogTemp, Warning, TEXT("INPUTE DE ATAQUEE"));

    if (AttackMontage)
    {
        PlayAnimMontage(AttackMontage);
    }
}
//aqui é uma gambiarrinha que quando apertar o botão de esquiva, vai tocar a anim,ação deesquiva e aparecer um LOG na tela

void AGuardianCharacter::Dodge()
{
    UE_LOG(LogTemp, Warning, TEXT("ESQUIVA INPUTE"));

    if (DodgeMontage)
    {
        PlayAnimMontage(DodgeMontage);
    }
}

//aqui é gamiarrinah tbm, mas só aparece o 'log' mesmo, não tem animação de interação ainda
void AGuardianCharacter::Interact()
{
    UE_LOG(LogTemp, Warning, TEXT("INPUTE DE INTERAÇÃO"));
}