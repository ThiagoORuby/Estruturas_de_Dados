# Get config of the project

keys = "qwertyuiopáãasdfghjklçéízxcvbnmóõôâê"
values = list(range(1, 13)) + list(range(11, 0, -2)) + list(range(11, 0, -2)) + list(range(2, 14, 2)) + list(range(2, 14, 2))
dict_name = {keys[i] : values[i] for i in range(len(keys))}

print(dict_name)

group_names = [
    "Diogo Tallys da Mota Amorim",
    "José Endson Santos",
    "Taisa Lima Silva",
    "Thiago Ribeiro Silva",
    "Hugo Coelho da Silva",
    "Diogo Travis Scott",
    "Diogo Mota Mota Amorim",
    "Caio Mascarenhas Soares"
]

options = [
    {
        0: "então você irá desenhar a planta de uma casa com 1 andar",
        1: "então você irá desenhar a planta de uma casa com 2 andares",
        2: "então você irá desenhar a planta de uma casa com 2 andares e um sótão",
        3 : "então você irá desenhar a planta de uma casa com 2 andares e um porão",
    },
    {
        0: "então você irá desenhar casa hexágono",
        1: "então você irá desenhar casa circunferência",
        2: "então você irá desenhar casa quadrada",
        3: "então você irá desenhar casa retangular",
    },
    {
        0: "então a casa terá um local de música",
        1: "então a casa terá uma sala de ginástica",
        2: "então a casa terá uma sala de estudo",
        3: "então a casa terá uma sala de jogos",
    },
    {
        0: "então a casa terá 3 quartos, 2 banheiro e 1 closet",
        1: "então a casa terá 2 quartos, 2 banheiro, 2 closet",
        2: "então a casa terá 3 quartos, 2 banheiro e 1 closet",
        3: "então a casa terá 2 quartos, 2 banheiro, 2 closet",
    }
]

def get_sum(name):
    s = 0
    for i in name.lower():
        if i != ' ':
            s += dict_name[i]
    return s


i = 0
for name in group_names:
    print(name)
    i = 0
    while(i <= 3):
        for sub in name.split(" "):
            s = get_sum(sub)
            print(f"Opção {i} = {s % 4} -> {options[i][s % 4]}")
            i += 1
            if(i > 3): break
    print()
