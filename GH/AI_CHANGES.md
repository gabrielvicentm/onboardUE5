# Registro de alterações feitas por IA

Este arquivo registra alterações realizadas pela IA/Codex no projeto UE5.

## 2026-07-01 19:06
### Arquivos alterados
- Source/GH/GHCharacter.h
- Source/GH/GHCharacter.cpp
- Source/GH/GHPlayerController.h
- Source/GH/GHPlayerController.cpp

### Alterações
- Removidos os campos e bindings de input de pulo (`JumpAction`) do personagem.
- Removidas as funções públicas `DoJumpStart` e `DoJumpEnd`.
- Desativado o pulo na configuração base do `CharacterMovement`.
- Removido o input separado `MouseLookAction`, deixando apenas `LookAction` para olhar/mirar.
- Removida a lógica de controles mobile/touch do `PlayerController`.
- Simplificado o `PlayerController` para adicionar apenas os `DefaultMappingContexts`.

### Motivo
- Reduzir o template Third Person ao necessário para o Dia 1 do onboarding: movimento, câmera e input básico estável em arena graybox.
- Evitar conflitos de câmera/input causados por ações duplicadas ou suporte mobile que não faz parte do protótipo atual.

### Observações
- Não foi feito build/compilação, conforme instrução do projeto.
- O Blueprint do personagem e os assets de input ainda precisam ser limpos no editor para remover referências antigas a pulo, mouse-look separado e controles touch.

## 2026-07-01 20:01
### Arquivos alterados
- Source/GH/GHCharacter.h
- Source/GH/GHCharacter.cpp
- Source/GH/Enemies/EnemyCharacter.h
- Source/GH/Enemies/EnemyCharacter.cpp

### Alterações
- Adicionado `HealthComponent` ao `AGHCharacter`.
- Adicionados parâmetros de ataque básico no `AGHCharacter`: dano, distância, raio, cooldown e debug visual.
- Adicionado `AttackAction` ao `AGHCharacter`, com bind protegido para evitar erro caso a Input Action ainda não esteja configurada no Blueprint.
- Implementado `DoAttack()` com overlap esférico na frente do player, seleção do alvo com `UHealthComponent`, aplicação de dano e `DrawDebugSphere`/`DrawDebugLine`.
- Criada a classe `AEnemyCharacter` com `HealthComponent`, perseguição simples ao player via `Tick`, ataque por proximidade com cooldown, logs de dano e morte placeholder com `Destroy()`.

### Motivo
- Dar continuidade ao Dia 2 do onboarding a partir da etapa 3.4: vida no player, inimigo básico, ataque do player e dano entre player/inimigo.

### Observações
- Não foi feito build/compilação, conforme instrução do projeto.
- Ainda é necessário criar/configurar no editor `IA_Attack`, mapear no `IMC_Default`, preencher `AttackAction` no Blueprint do personagem e criar `BP_Enemy_Basic` derivado de `AEnemyCharacter`.
- A IA do inimigo é propositalmente simples para o Dia 2; NavMesh, Behavior Tree e sequestro da princesa ficam para dias posteriores.

## 2026-07-01 20:03
### Arquivos alterados
- Source/GH/GHCharacter.cpp

### Alterações
- Adicionado include explícito de `Engine/OverlapResult.h`.

### Motivo
- Corrigir erro de compilação causado pelo uso de `FOverlapResult::GetActor()` com o tipo ainda incompleto no `GHCharacter.cpp`.

### Observações
- Não foi feito build/compilação, conforme instrução do projeto.
- O warning sobre diretório inexistente em `GH.Build.cs` não parece ser a causa da falha atual; ele pode ser limpo depois removendo include paths antigos do template.
