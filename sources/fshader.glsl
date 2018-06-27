#version 130

uniform sampler2D textureMap0;
uniform sampler2D textureMap1;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

in vec4 l; //wektor do swiatla(przestrzen oka)
in vec4 v; //wektor do obserwatora(przestrzen oka)
in vec4 n; //wektor normalny (przestrzen oka)
in vec2 iTexCoord0; //wspolrzedne teksturowania
in vec4 fragPos;
in vec4 dirLightPosition;
in vec4 pointLightPosition;
in vec4 specLightPosition;
//ks specular 
//kd deffuse
//ka ambient
//alpha shinnines
struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadratic;
    
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
 
};
struct DirLight{
    vec4 direction;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

};
PointLight initPL(){
     PointLight pointLight;
    pointLight.ambient = vec4(0.5);
    pointLight.diffuse = vec4(0.8);
    pointLight.specular = vec4(0.6);
    pointLight.constant = 1.0f;
    pointLight.linear = 0.07f;
    pointLight.quadratic =0.017f;
    return pointLight;
}
DirLight initDL(){
    DirLight dirLight;
    //dirLight.ambient = vec4(0.1);
    dirLight.ambient = vec4(vec3(0.1),1);
    dirLight.diffuse = vec4(0.3);
    dirLight.specular = vec4(0.2);
    return dirLight;
}

vec4 calcDirLight(DirLight dirLight,vec4 normal ,vec4 viewDir){
    vec4 lightDir = normalize(-dirLightPosition);
    float diff  = max(dot(normal,lightDir),0.0);
    vec4 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),10);
    vec4 ka=dirLight.ambient*vec4(0.1); //Kolor obiektu w swietle otoczenia
    vec4 kd=dirLight.diffuse* diff*texture(textureMap0,iTexCoord0); //Kolor obiektu w swietle rozproszonym
    vec4 ks=dirLight.specular* spec*vec4(0.1); //Kolor obiektu w swietle odbitym
    return (ka+kd+ks);
}
vec4 calcPointLight(PointLight pointLight, vec4 normal, vec4 viewDir){
    vec4 lightDir = normalize(-pointLightPosition);
    float diff = max(dot(normal,lightDir),0.0);
    vec4 reflectDir = reflect(-lightDir,normal);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),10);
    float distnace = length(pointLightPosition-fragPos);
    float atteunation = 1.0/(pointLight.constant+distnace*pointLight.linear+pointLight.quadratic*(distnace*distnace));
    vec4 ambient = pointLight.ambient*vec4(0.1);
    vec4 diffuse = pointLight.diffuse*diff*texture(textureMap0,iTexCoord0);
    vec4 specular = pointLight.specular*spec*vec4(0.1);
    ambient*=atteunation;
    diffuse*=atteunation;
    specular*=atteunation;
    return (ambient+diffuse+specular);
}
void main(void) {
    PointLight pointLight=initPL();
    DirLight dirLight=initDL();

    vec4 ka=vec4(0.1); //Kolor obiektu w swietle otoczenia
    vec4 kd=texture(textureMap0,iTexCoord0); //Kolor obiektu w swietle rozproszonym
    vec4 ks=vec4(0.1); //Kolor obiektu w swietle odbitym

    vec4 la=vec4(0.1); //Kolor swiatla otoczenia
    vec4 ld=vec4(0.5); //Kolor swiatla rozpraszanego
    vec4 ls=vec4(0.2); //Kolor swiatla odbijanego

    vec4 ml=normalize(l);//wektor do swiatla
    vec4 mn=normalize(n); //wektor normalny 
    vec4 mv=normalize(v); //wektor do obserwatora
    vec4 mr=reflect(-ml,mn); //wektor odbity

    float nl=max(dot(mn,ml),0); //Kosinus kata pomiedzy wektorami do swiatla i normalnym
    float rv=pow(max(dot(mr,mv),0),10); //Kosinus kata pomiedzy wektorami odbitym i do obserwatora do potegi 10
    vec4 result ;
    result =calcDirLight(dirLight,n,v);
    result +=calcPointLight(pointLight,n,v);

    pixelColor = result;
	//pixelColor=ka*pointLight.ambient+kd*pointLight.diffuse*vec4(nl,nl,nl,1)+ks*pointLight.specular*rv; //Model oswietlenia Phonga
}
