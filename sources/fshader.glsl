#version 130

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 l; //wektor do swiatla(przestrzen oka)
in vec4 v; //wektor do obserwatora(przestrzen oka)
in vec4 n; //wektor normalny (przestrzen oka)
in vec2 iTexCoord0; //wspolrzedne teksturowania


void main(void) {
 vec4 ka=vec4(0,0,0,0); //Kolor obiektu w swietle otoczenia
    vec4 kd=texture(textureMap0,iTexCoord0); //Kolor obiektu w swietle rozproszonym
    vec4 ks=vec4(0,0,0,0); //Kolor obiektu w swietle odbitym

    vec4 la=vec4(0,0,0,0); //Kolor swiatla otoczenia
    vec4 ld=vec4(1,1,1,1); //Kolor swiatla rozpraszanego
    vec4 ls=vec4(1,1,1,0); //Kolor swiatla odbijanego

    vec4 ml=normalize(l);
    vec4 mn=normalize(n);
    vec4 mv=normalize(v);
    vec4 mr=reflect(-ml,mn);

    float nl=max(dot(mn,ml),0); //Kosinus kata pomiedzy wektorami do swiatla i normalnym
    float rv=pow(max(dot(mr,mv),0),10); //Kosinus kata pomiedzy wektorami odbitym i do obserwatora do potegi 10

	pixelColor=ka*la+kd*ld*vec4(nl,nl,nl,1)+ks*ls*rv; //Model oswietlenia Phonga
}
