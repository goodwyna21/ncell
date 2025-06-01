import re

#use https://realazy.com/enough-shadcn-ui-colors/ to generate color palettes
#I used https://realazy.com/enough-shadcn-ui-colors/#360,100,51,70,68

colDefPattern = r"([a-zA-Z_\d]+)\s+(#[0-9a-fA-F]{6})"
pairPattern = r"([a-zA-Z_\d]+) ([a-zA-Z_\d]+) ([a-zA-Z_\d]+)"

color_hex = {}
pairs = {}
with open("../config/colors.txt", 'r') as colFile:
    #read color definitions
    for colDef in colFile:
        if ';' in colDef:
            break
        srch = re.match(colDefPattern, colDef)
        if srch == None:
            continue
        color_hex.update({srch.group(1) : srch.group(2)})
    for pairDef in colFile:
        srch = re.match(pairPattern, pairDef)
        if srch == None:
            continue
        pairs.update({srch.group(1) : [srch.group(2), srch.group(3)]})
for pair, cols in pairs.items():
    print(pair, cols)

with open("colorTest.html",'w') as out:
    out.write("""<html><head><style>
.colorSample {
    border-style: solid;
    border-color: black;
    width: 90px;
    height: 90px;
    display: inline-block;
    flex-wrap: wrap;
    border-radius: 10px;
}
</style></head><body>
""")
    for col, hex in color_hex.items():
        out.write(f"<div class=\"colorSample\" style=\"background-color:{hex}\"><mark>{col}</mark></div>\n")
    for pair, cols in pairs.items():
        out.write(f"<p><mark style=\"background-color:{color_hex[cols[1]]};color:{color_hex[cols[0]]}\">{pair}</mark></p>")
    out.write("</body></html>")

'''
<html><body>
<div class="box color1"></div>
<div class="box color2"></div>
...
</body></html>
'''
