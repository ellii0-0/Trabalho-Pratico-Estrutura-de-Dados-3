import subprocess
import unicodedata


executavel = "./programaTrab"


print("Limpando...")
resultado = subprocess.run(
        ["make", "clean"],
        capture_output=True,
        text=True
)

if resultado.returncode != 0:
        print("Erro ao executar 'make clean':")
        print(resultado.stderr)
        exit(1)


print("Compilando...")
resultado = subprocess.run(
        ["make", "all", "BUILD_MODE=DEBUG", "ASAN=1"],
        capture_output=True,
        text=True
)

if resultado.returncode != 0:
        print("Erro ao executar 'make all':")
        print(resultado.stderr)
        exit(1)


def remover_caracteres_invisiveis(texto):
        return "".join(
                caractere for caractere in texto
                if caractere in "\n\t "
                or not unicodedata.category(caractere).startswith("C")
        )


print()

for i in range(1, 12):
        with open(f"casos-t1/{i}.in", "r", encoding="utf-8") as arquivo:
                entrada = arquivo.read()

        with open(f"casos-t1/{i}.out", "r", encoding="utf-8") as arquivo:
                esperado = arquivo.read()

        resultado = subprocess.run(
                [executavel],
                input=entrada,
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                text=True
        )

        obtido = resultado.stdout

        esperado = remover_caracteres_invisiveis(esperado)
        obtido = remover_caracteres_invisiveis(obtido)

        if obtido == esperado:
                print(f"Caso {i}: OK")
        else:
                print(f"Caso {i}: ERRO")

                print("\n--- Esperado ---")
                print(esperado, end="")

                print("\n--- Obtido ---")
                print(obtido, end="")

                if resultado.stderr:
                        print("\n--- stderr ---")
                        print(resultado.stderr)