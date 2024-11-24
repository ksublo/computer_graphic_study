Aktuální stav

1. Přepínání scén za běhu - ANO
--KDE ?? metoda switchScene() - AppController a keyCallback(),render() - Application
--JAK ?? switchScene poslusha stisk klaves (1-4), na zaklade ceho urcuje se cislo sceny
         render() renderuje aktualnu scenu
         keyCallback() vola switcScene() a dalse metody

a) Základní scéna - ANO

b) Scéna s lesem - ANO

c) Scéna se čtyřmi kuličkami - ANO

d) Scéna pro demonstraci použití všech shaderů (Konstantní, Lambert, Phong a Blinn) - ANO

2. Světlo - ANO
--KDE ?? class Light definuje svetlo, ShaderProgram nastavuje vlastnosti, SceneInicializer vytvari instance a nastavi je pro shader modely
--JAK ?? pomoci Observer, kde shaderProgram je jako pozorovatel, pri zmene aktualizace pomoci update()

3. Základní třídy (ShaderProgram, DrowableObject, Camera, Controller) - ANO 
--DrawableObject - predstavuje objecty ktery lze vykreslovat ve scene - resi draw a transformace
--ShaderProgram - zodpovida za vertex a fragment shaders, nastavuje svetlo a kameru
--Scene - uchovava vsechny objecty, vykresluje a transformuje
--AppController - ridi interakce usera ze scenou, ovladani kamery, prepinany scen, rotace a transformace
--SceneInicializer - inicializace jednotlivych scen 
--Camera - zodpovida za zobrazeni, navrh pomoci Observeru

4. Transformace (Composite pattern) - ANO 
--zakladni virtualni trida Transformation z metodou getMAtrix(), kteru prepsujem v dalshich tridach (Scale, Rotation, Translation, TransformationGroup)
--TransformationGroup - umoznuje kombinovat vice transformaci 
--Rotation - uklada uhel a osu rotace 
--Scale - uklada meritko
--Traslation - uklada posun v osach X,Y,Z

Základy OOP

a) Encapsulation (zapouzdření) - ANO
napriklad: ShaderProgram - programID, camera, light
           Object - VAO, VBO, vertexCount
           atd...

b) Inheritance (dědičnost) - ANO
napriklad: Transformation z podtridami Scale, Translation ... (pri vzoru Composite)
           Subject - Light a Camera (pri vzoru Observer)
           ShaderLoader - ShaderProgram 

c) Polymorphism (polymorfismus neboli mnohotvárnost) - ANO
napriklad: Transformation - getMatrix();
           Subject - spravuje seznam Observer*, jakykoli observer muze byt registrovan jako pozorovatel
                for (Observer* observer : observers) {
                    observer->update();
                }
           SceneInicializer pri vytvareni a nastovovani objectu a shaderu ve scenach, vytvori objekty pomoci ukazatelu DrawableObject*,
                aplikuje transformace Transformation* a podobne...

                

6. Vertex a fragment shadery prosím uložte do textových souboru a použijte přiložený ShaderLoader pro jejich načítání - ANO
--Ulozila jsem to do glsl souboru
--Ve sceneInicializeru pouzivala jsem to primo pri vytvareni shaderPorgramu, protoze shaderProgram dedi ShaderLoader ktery to zpracuje
    a primo ve konstruktoru ShaderProgramu vyuzivam loadShader() ktery resi compilace a nacitani souboru.