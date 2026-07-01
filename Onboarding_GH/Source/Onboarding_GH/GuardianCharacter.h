#pragma once //serve para que o arquivo seja incluido apenas uam vez na hora de compilar, pra evitar erro de compilação

#include "CoreMinimal.h" //esse include é o include base da Unreal Engine, ele inclui as definições básicas da engine, tipos de dados, macros...
#include "GameFramework/Character.h" //esse include é o do Character que é a classe pai da classe que eu criei(AGuardianCharacter), que é a classe que define o personagem do jogo, e que eu herdo para criar o meu personagem  
#include "InputActionValue.h" //esse include é a casse que define o valor do input, uso para pegar o input do jogador e transformar em movimento do personagem
//OBS: esse sempre tem que ser o último include
#include "GuardianCharacter.generated.h" //é o arquivo gerado pela UE5 que contém os paranaue que precisa.

//aqui eu crio as classes que eu vou usar no .h da classe
class UCameraComponent; 
class USpringArmComponent;
class UInputAction;
class UInputMappingContext;
class UAnimMontage;

//essa UCLASS() é um macro que serve para a UE registrar essa classe como pertencente a Engine, e não como um classe c++ genérica e descartável
UCLASS()
class ONBOARDING_GH_API AGuardianCharacter : public ACharacter // aqui eu crio a classe AGuardianCharacter, que é a classe do personagem do jogo, e que herda da classe ACharacter, que é a classe base da Unreal Engine para personagens
{
    GENERATED_BODY() //esse macro é utilizado para gerar código boilerplate, que é o código que a Unreal Engine precisa para registrar a classe como pertencente a Engine, e não como um classe c++ genérica e descartável

public:
    AGuardianCharacter(); //aqui eu crio o construtor da classe, que é a função que é chamada quando o personagem é criado, e que é utilizada para inicializar as variáveis da classe

protected: 
    virtual void BeginPlay() override; //crio a função BeginPlay() que é a função chamada quando o jogo inicia, e que é utilizada para inicializar as variáveis da classe, e que é sobrescrita da classe ACharacter
    //a função SetupPlayerInput Componnet é a func chamada quando o jogador aperta os botões do input, e que é utilizada para bindar as ações de input do persoangem
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    //aqui eu crio as variáveis da classe, que são os componentes do personagem, e que são utilizadas para definir a aparência e o comportamento do personagem
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
    TObjectPtr<UInputMappingContext> DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
    TObjectPtr<UInputAction> AttackAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
    TObjectPtr<UInputAction> DodgeAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input")
    TObjectPtr<UInputAction> InteractAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation")
    TObjectPtr<UAnimMontage> AttackMontage;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Animation")
    TObjectPtr<UAnimMontage> DodgeMontage;

    //aqui é a variável que define a velocidade de movimentação, por padrão é 400
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
    float WalkSpeed = 400.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Movement")
    float RunSpeed = 650.0f;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Attack();
    void Dodge();
    void Interact();
};