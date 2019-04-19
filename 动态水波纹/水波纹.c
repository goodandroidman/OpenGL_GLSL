//性能良好：在Max8设备上，性能良好


//顶点着色器
attribute vec3 kzPosition;
attribute vec2 kzTextureCoordinate0;
uniform highp mat4 kzProjectionCameraWorldMatrix;

varying mediump vec2 vTexCoord;

void main()
{
    precision mediump float;
    
    vTexCoord = kzTextureCoordinate0;
    gl_Position = kzProjectionCameraWorldMatrix * vec4(kzPosition.xyz, 1.0);
}


//片元着色器

uniform sampler2D Texture;
uniform lowp float BlendIntensity;
uniform sampler2D MaskTexture;
varying mediump vec2 vTexCoord;

uniform mediump vec2 TextureOffset;
uniform mediump vec2 TextureTiling;
uniform mediump vec2 MaskTextureOffset;
uniform mediump vec2 MaskTextureTiling;

uniform highp float kzTime;

uniform mediump float VoiceAnimation;
void main()
{
    precision lowp float;
    
    float dist = 200.0*length(vTexCoord-vec2(0.5));
    
    float circlesOut = cos((dist-10.0*kzTime)/2.0);
    circlesOut *= 2.0;
    
    float circlesIn = cos((dist-10.0*kzTime)/2.0);
    circlesIn *= 2.0;
    
    circlesIn = clamp(circlesIn,0.0,1.0);
    circlesOut = clamp(circlesOut,0.0,1.0);
    
    float edge = clamp(dist,0.0,1.0);
    circlesOut *= edge;
    circlesIn *= 0.5-edge;
    float c = circlesOut + circlesIn;
    vec4 color = texture2D(Texture, vTexCoord);
    gl_FragColor = vec4(c)*color.a;
}