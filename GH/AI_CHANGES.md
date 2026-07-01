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
