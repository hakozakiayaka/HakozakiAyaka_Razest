xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 244;
 69.00287;20.49646;61.01009;,
 86.15517;20.49647;65.59084;,
 86.15517;8.96080;65.59084;,
 69.00286;8.96080;61.01009;,
 93.25993;20.49646;76.64971;,
 93.25993;8.96080;76.64971;,
 86.15517;20.49647;87.70850;,
 86.15517;8.96080;87.70850;,
 69.00285;20.49646;92.28921;,
 69.00285;8.96079;92.28921;,
 51.85046;20.49647;87.70850;,
 51.85046;8.96079;87.70850;,
 44.74577;20.49646;76.64971;,
 44.74577;8.96080;76.64971;,
 51.85046;20.49647;65.59084;,
 51.85046;8.96079;65.59084;,
 69.00287;20.49646;61.01009;,
 69.00286;8.96080;61.01009;,
 69.00287;20.49646;76.64971;,
 69.00287;20.49646;76.64971;,
 69.00287;20.49646;76.64971;,
 69.00287;20.49646;76.64971;,
 69.00287;20.49646;76.64971;,
 69.00287;20.49646;76.64971;,
 69.00287;20.49646;76.64971;,
 69.00287;20.49646;76.64971;,
 69.00286;8.96080;76.64971;,
 69.00286;8.96080;76.64971;,
 69.00286;8.96080;76.64971;,
 69.00286;8.96080;76.64971;,
 69.00286;8.96080;76.64971;,
 69.00286;8.96080;76.64971;,
 69.00286;8.96080;76.64971;,
 69.00286;8.96080;76.64971;,
 69.00287;134.81252;61.01009;,
 86.15517;134.81252;65.59084;,
 86.15517;123.27680;65.59084;,
 69.00287;123.27682;61.01009;,
 93.25992;134.81250;76.64971;,
 93.25993;123.27682;76.64971;,
 86.15517;134.81252;87.70850;,
 86.15517;123.27680;87.70850;,
 69.00284;134.81250;92.28921;,
 69.00284;123.27682;92.28921;,
 51.85046;134.81250;87.70850;,
 51.85046;123.27682;87.70850;,
 44.74577;134.81250;76.64971;,
 44.74577;123.27682;76.64971;,
 51.85046;134.81250;65.59084;,
 51.85046;123.27682;65.59084;,
 69.00287;134.81252;61.01009;,
 69.00287;123.27682;61.01009;,
 69.00287;134.81252;76.64971;,
 69.00287;134.81252;76.64971;,
 69.00287;134.81252;76.64971;,
 69.00287;134.81252;76.64971;,
 69.00287;134.81252;76.64971;,
 69.00287;134.81252;76.64971;,
 69.00287;134.81252;76.64971;,
 69.00287;134.81252;76.64971;,
 69.00287;123.27682;76.64971;,
 69.00287;123.27682;76.64971;,
 69.00287;123.27682;76.64971;,
 69.00287;123.27682;76.64971;,
 69.00287;123.27682;76.64971;,
 69.00287;123.27682;76.64971;,
 69.00287;123.27682;76.64971;,
 69.00287;123.27682;76.64971;,
 69.00287;20.49646;-80.80519;,
 86.15517;20.49647;-76.22444;,
 86.15517;8.96080;-76.22444;,
 69.00286;8.96080;-80.80519;,
 93.25993;20.49646;-65.16549;,
 93.25993;8.96080;-65.16549;,
 86.15517;20.49647;-54.10677;,
 86.15517;8.96080;-54.10677;,
 69.00285;20.49646;-49.52595;,
 69.00285;8.96079;-49.52595;,
 51.85046;20.49647;-54.10677;,
 51.85046;8.96079;-54.10677;,
 44.74577;20.49646;-65.16549;,
 44.74577;8.96080;-65.16549;,
 51.85046;20.49647;-76.22444;,
 51.85046;8.96079;-76.22444;,
 69.00287;20.49646;-80.80519;,
 69.00286;8.96080;-80.80519;,
 69.00287;20.49646;-65.16549;,
 69.00287;20.49646;-65.16549;,
 69.00287;20.49646;-65.16549;,
 69.00287;20.49646;-65.16549;,
 69.00287;20.49646;-65.16549;,
 69.00287;20.49646;-65.16549;,
 69.00287;20.49646;-65.16549;,
 69.00287;20.49646;-65.16549;,
 69.00286;8.96080;-65.16549;,
 69.00286;8.96080;-65.16549;,
 69.00286;8.96080;-65.16549;,
 69.00286;8.96080;-65.16549;,
 69.00286;8.96080;-65.16549;,
 69.00286;8.96080;-65.16549;,
 69.00286;8.96080;-65.16549;,
 69.00286;8.96080;-65.16549;,
 69.00287;134.81252;-80.80519;,
 86.15517;134.81252;-76.22444;,
 86.15517;123.27680;-76.22444;,
 69.00287;123.27682;-80.80519;,
 93.25992;134.81250;-65.16549;,
 93.25993;123.27682;-65.16549;,
 86.15517;134.81252;-54.10677;,
 86.15517;123.27680;-54.10677;,
 69.00284;134.81250;-49.52595;,
 69.00284;123.27682;-49.52595;,
 51.85046;134.81250;-54.10677;,
 51.85046;123.27682;-54.10677;,
 44.74577;134.81250;-65.16549;,
 44.74577;123.27682;-65.16549;,
 51.85046;134.81250;-76.22444;,
 51.85046;123.27682;-76.22444;,
 69.00287;134.81252;-80.80519;,
 69.00287;123.27682;-80.80519;,
 69.00287;134.81252;-65.16549;,
 69.00287;134.81252;-65.16549;,
 69.00287;134.81252;-65.16549;,
 69.00287;134.81252;-65.16549;,
 69.00287;134.81252;-65.16549;,
 69.00287;134.81252;-65.16549;,
 69.00287;134.81252;-65.16549;,
 69.00287;134.81252;-65.16549;,
 69.00287;123.27682;-65.16549;,
 69.00287;123.27682;-65.16549;,
 69.00287;123.27682;-65.16549;,
 69.00287;123.27682;-65.16549;,
 69.00287;123.27682;-65.16549;,
 69.00287;123.27682;-65.16549;,
 69.00287;123.27682;-65.16549;,
 69.00287;123.27682;-65.16549;,
 -68.99577;121.30116;-72.57286;,
 -68.99577;135.88422;-72.57286;,
 47.13013;135.88422;-72.57286;,
 47.13013;121.30116;-72.57286;,
 -68.99577;135.88422;-72.57286;,
 -68.99577;135.88422;85.63389;,
 47.13013;135.88422;85.63389;,
 47.13013;135.88422;-72.57286;,
 -68.99577;135.88422;85.63389;,
 -68.99577;121.30116;85.63389;,
 47.13013;121.30116;85.63389;,
 47.13013;135.88422;85.63389;,
 -68.99577;121.30116;85.63389;,
 -68.99577;121.30116;-72.57286;,
 47.13013;121.30116;-72.57286;,
 47.13013;121.30116;85.63389;,
 -68.99577;135.88422;-72.57286;,
 -68.99577;121.30116;-72.57286;,
 47.13013;121.30116;-72.57286;,
 47.13013;135.88422;-72.57286;,
 -68.99576;8.18533;-72.57286;,
 -68.99579;22.76838;-72.57286;,
 47.13013;22.76838;-72.57286;,
 47.13012;8.18533;-72.57286;,
 -68.99579;22.76838;-72.57286;,
 -68.99579;22.76838;85.63389;,
 47.13013;22.76838;85.63389;,
 47.13013;22.76838;-72.57286;,
 -68.99579;22.76838;85.63389;,
 -68.99576;8.18533;85.63389;,
 47.13012;8.18533;85.63389;,
 47.13013;22.76838;85.63389;,
 -68.99576;8.18533;85.63389;,
 -68.99576;8.18533;-72.57286;,
 47.13012;8.18533;-72.57286;,
 47.13012;8.18533;85.63389;,
 -68.99579;22.76838;-72.57286;,
 -68.99576;8.18533;-72.57286;,
 47.13012;8.18533;-72.57286;,
 47.13013;22.76838;-72.57286;,
 -68.42808;130.52850;-72.57286;,
 -48.46128;130.52850;-72.57286;,
 -48.46127;8.46402;-72.57286;,
 -68.42810;8.46403;-72.57286;,
 -48.46128;130.52850;-72.57286;,
 -48.46128;130.52850;85.63389;,
 -48.46127;8.46402;85.63389;,
 -48.46127;8.46402;-72.57286;,
 -48.46128;130.52850;85.63389;,
 -68.42808;130.52850;85.63389;,
 -68.42810;8.46403;85.63389;,
 -48.46127;8.46402;85.63389;,
 -68.42808;130.52850;85.63389;,
 -68.42808;130.52850;-72.57286;,
 -68.42810;8.46403;-72.57286;,
 -68.42810;8.46403;85.63389;,
 -48.46128;130.52850;-72.57286;,
 -68.42808;130.52850;-72.57286;,
 -68.42810;8.46403;-72.57286;,
 -48.46127;8.46402;-72.57286;,
 28.89169;130.52850;-72.57286;,
 48.85852;130.52850;-72.57286;,
 48.85852;8.46403;-72.57286;,
 28.89169;8.46403;-72.57286;,
 48.85852;130.52850;-72.57286;,
 48.85852;130.52850;85.63389;,
 48.85852;8.46403;85.63389;,
 48.85852;8.46403;-72.57286;,
 48.85852;130.52850;85.63389;,
 28.89169;130.52850;85.63389;,
 28.89169;8.46403;85.63389;,
 48.85852;8.46403;85.63389;,
 28.89169;130.52850;85.63389;,
 28.89169;130.52850;-72.57286;,
 28.89169;8.46403;-72.57286;,
 28.89169;8.46403;85.63389;,
 48.85852;130.52850;-72.57286;,
 28.89169;130.52850;-72.57286;,
 28.89169;8.46403;-72.57286;,
 48.85852;8.46403;-72.57286;,
 -65.40166;120.16940;-77.13068;,
 -64.83353;25.04625;-77.13068;,
 26.45795;25.04625;-77.13068;,
 26.45794;120.16940;-77.13068;,
 -64.83353;25.04625;-77.13068;,
 -65.40166;120.16940;-77.13068;,
 -56.76041;119.91776;-98.80571;,
 -56.76041;24.79458;-98.80571;,
 -13.32005;120.72702;-123.56271;,
 18.83955;120.48063;-124.74258;,
 18.83955;25.35744;-124.74258;,
 -12.30400;25.60378;-123.72698;,
 -56.76041;24.79458;-98.80571;,
 -56.76041;119.91776;-98.80571;,
 27.95573;120.41052;-114.00838;,
 18.83955;120.48063;-124.74258;,
 -13.32005;120.72702;-123.56271;,
 -56.76041;119.91776;-98.80571;,
 26.45794;120.16940;-77.13068;,
 -12.30400;25.60378;-123.72698;,
 18.83955;25.35744;-124.74258;,
 27.89030;25.28892;-114.26095;,
 26.45795;25.04625;-77.13068;,
 -56.76041;24.79458;-98.80571;,
 27.95573;120.41052;-114.00838;,
 27.89030;25.28892;-114.26095;,
 18.83955;25.35744;-124.74258;,
 18.83955;120.48063;-124.74258;;
 
 132;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 3;60,37,36;,
 3;61,36,39;,
 3;62,39,41;,
 3;63,41,43;,
 3;64,43,45;,
 3;65,45,47;,
 3;66,47,49;,
 3;67,49,51;,
 4;68,69,70,71;,
 4;69,72,73,70;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 3;86,69,68;,
 3;87,72,69;,
 3;88,74,72;,
 3;89,76,74;,
 3;90,78,76;,
 3;91,80,78;,
 3;92,82,80;,
 3;93,84,82;,
 3;94,71,70;,
 3;95,70,73;,
 3;96,73,75;,
 3;97,75,77;,
 3;98,77,79;,
 3;99,79,81;,
 3;100,81,83;,
 3;101,83,85;,
 4;102,103,104,105;,
 4;103,106,107,104;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 3;120,103,102;,
 3;121,106,103;,
 3;122,108,106;,
 3;123,110,108;,
 3;124,112,110;,
 3;125,114,112;,
 3;126,116,114;,
 3;127,118,116;,
 3;128,105,104;,
 3;129,104,107;,
 3;130,107,109;,
 3;131,109,111;,
 3;132,111,113;,
 3;133,113,115;,
 3;134,115,117;,
 3;135,117,119;,
 4;136,137,138,139;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;148,141,152,153;,
 4;154,155,142,151;,
 4;156,157,158,159;,
 4;160,161,162,163;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;168,161,172,173;,
 4;174,175,162,171;,
 4;176,177,178,179;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;188,181,192,193;,
 4;194,195,182,191;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;208,209,210,211;,
 4;208,201,212,213;,
 4;214,215,202,211;,
 4;216,217,218,219;,
 4;220,221,222,223;,
 4;224,225,226,227;,
 4;224,227,228,229;,
 3;230,231,232;,
 4;230,232,233,221;,
 3;230,221,234;,
 3;235,236,237;,
 4;235,237,238,220;,
 3;235,220,239;,
 4;240,234,238,241;,
 4;240,241,242,243;;
 
 MeshMaterialList {
  2;
  132;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.244706;0.668235;0.668235;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.332549;0.332549;0.332549;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  153;
  -0.000000;1.000000;-0.000000;,
  0.000001;-0.000000;-1.000000;,
  0.589436;-0.000000;-0.807815;,
  0.841335;-0.000001;-0.540514;,
  0.589433;-0.000000;0.807817;,
  0.000001;-0.000000;1.000000;,
  -0.589435;-0.000000;0.807816;,
  -0.841335;-0.000000;0.540514;,
  -0.589437;-0.000000;-0.807814;,
  0.000000;-1.000000;-0.000000;,
  0.841333;-0.000001;0.540518;,
  -0.841337;-0.000000;-0.540510;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000001;,
  0.000000;-1.000000;-0.000001;,
  0.000000;-1.000000;-0.000000;,
  0.000001;-1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000001;0.000000;-1.000000;,
  0.589436;0.000000;-0.807815;,
  0.841335;0.000001;-0.540514;,
  0.589433;0.000000;0.807817;,
  0.000000;-0.000000;1.000000;,
  -0.589435;-0.000000;0.807816;,
  -0.841335;-0.000001;0.540514;,
  -0.589437;-0.000000;-0.807815;,
  -0.000000;-1.000000;0.000000;,
  0.841333;0.000001;0.540517;,
  -0.841337;-0.000001;-0.540511;,
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000001;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;0.000001;,
  -0.000000;1.000000;0.000001;,
  -0.000001;1.000000;0.000000;,
  -0.000001;1.000000;-0.000000;,
  -0.000001;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000001;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;-0.000001;,
  -0.000001;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000001;,
  0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.000001;-0.000000;-1.000000;,
  0.589437;-0.000000;-0.807814;,
  0.841336;-0.000001;-0.540512;,
  0.589435;-0.000000;0.807816;,
  0.000000;-0.000000;1.000000;,
  -0.589436;-0.000000;0.807815;,
  -0.841334;-0.000000;0.540516;,
  -0.589438;-0.000000;-0.807813;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000001;0.000000;-1.000000;,
  0.589437;0.000000;-0.807814;,
  0.841337;0.000001;-0.540511;,
  0.589435;0.000000;0.807816;,
  0.000000;-0.000000;1.000000;,
  -0.589436;-0.000000;0.807815;,
  -0.841334;-0.000001;0.540516;,
  -0.589438;-0.000000;-0.807813;,
  -0.000000;-1.000000;0.000000;,
  0.841331;-0.000001;0.540520;,
  -0.841339;-0.000000;-0.540508;,
  -0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000001;,
  0.000000;-1.000000;-0.000001;,
  0.000000;-1.000000;-0.000000;,
  0.000001;-1.000000;0.000000;,
  0.841332;0.000001;0.540519;,
  -0.841339;-0.000001;-0.540508;,
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  0.000001;1.000000;-0.000000;,
  0.000000;1.000000;-0.000000;,
  -0.000000;1.000000;0.000001;,
  -0.000000;1.000000;0.000001;,
  -0.000001;1.000000;0.000000;,
  -0.000001;1.000000;-0.000000;,
  -0.000001;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000001;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;-1.000000;-0.000001;,
  -0.000001;-1.000000;0.000000;,
  -0.000000;-1.000000;0.000001;,
  0.000000;-1.000000;0.000000;,
  -0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000001;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  -0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;-0.000002;0.000000;,
  1.000000;-0.000001;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000001;-1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.756961;-0.002480;-0.653456;,
  0.402274;0.000707;-0.915519;,
  0.000000;-0.000000;1.000000;,
  -0.271096;-0.000631;-0.962552;,
  -0.005510;-0.999974;-0.004543;,
  0.001148;0.999986;0.005154;,
  -0.933073;-0.002774;-0.359676;,
  0.007662;0.999971;0.000024;,
  0.001722;0.999989;0.004463;,
  -0.004219;0.999951;0.008901;,
  -0.002109;0.999968;0.007720;,
  0.000000;0.999979;0.006538;,
  0.006732;-0.999966;0.004715;,
  -0.007900;-0.999969;0.000284;,
  -0.003119;-0.999951;-0.009370;,
  0.014049;-0.999877;0.006930;,
  0.031209;-0.999243;0.023226;,
  0.944641;0.000113;-0.328105;,
  0.999217;-0.000397;0.039562;;
  132;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;10,4,4,10;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;11,8,8,11;,
  4;8,1,1,8;,
  3;0,12,13;,
  3;0,14,12;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,17,16;,
  3;0,14,17;,
  3;0,18,14;,
  3;0,13,18;,
  3;9,19,20;,
  3;9,20,21;,
  3;9,21,22;,
  3;9,22,23;,
  3;9,23,24;,
  3;9,24,25;,
  3;9,25,26;,
  3;9,26,19;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;37,31,31,37;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;38,35,35,38;,
  4;35,28,28,35;,
  3;27,39,40;,
  3;27,41,39;,
  3;27,42,41;,
  3;27,43,42;,
  3;27,44,43;,
  3;27,45,44;,
  3;27,46,45;,
  3;27,40,46;,
  3;36,47,48;,
  3;36,48,49;,
  3;36,49,50;,
  3;36,50,51;,
  3;36,51,52;,
  3;36,52,53;,
  3;36,53,54;,
  3;36,54,47;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;75,59,59,75;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;76,63,63,76;,
  4;63,56,56,63;,
  3;55,77,78;,
  3;55,79,77;,
  3;55,80,79;,
  3;55,81,80;,
  3;55,82,81;,
  3;55,79,82;,
  3;55,83,79;,
  3;55,78,83;,
  3;64,84,85;,
  3;64,85,86;,
  3;64,86,87;,
  3;64,87,88;,
  3;64,88,89;,
  3;64,89,90;,
  3;64,90,91;,
  3;64,91,84;,
  4;66,67,67,66;,
  4;67,68,68,67;,
  4;92,69,69,92;,
  4;69,70,70,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;93,73,73,93;,
  4;73,66,66,73;,
  3;65,94,95;,
  3;65,96,94;,
  3;65,97,96;,
  3;65,98,97;,
  3;65,99,98;,
  3;65,100,99;,
  3;65,101,100;,
  3;65,95,101;,
  3;74,102,103;,
  3;74,103,104;,
  3;74,104,105;,
  3;74,105,106;,
  3;74,106,107;,
  3;74,107,108;,
  3;74,108,109;,
  3;74,109,102;,
  4;110,110,110,110;,
  4;111,111,111,111;,
  4;112,112,112,112;,
  4;113,113,113,113;,
  4;114,114,114,114;,
  4;115,115,115,115;,
  4;116,116,116,116;,
  4;117,117,117,117;,
  4;118,118,118,118;,
  4;119,119,119,119;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;125,125,125,125;,
  4;126,126,126,126;,
  4;127,127,127,127;,
  4;128,128,128,128;,
  4;129,129,129,129;,
  4;130,130,130,130;,
  4;131,131,131,131;,
  4;132,132,132,132;,
  4;133,133,133,133;,
  4;136,136,136,136;,
  4;140,140,134,134;,
  4;137,135,135,137;,
  4;137,137,134,134;,
  3;139,141,142;,
  4;139,142,143,144;,
  3;139,144,145;,
  3;146,147,138;,
  4;146,138,148,149;,
  3;146,149,150;,
  4;151,152,152,151;,
  4;151,151,135,135;;
 }
 MeshTextureCoords {
  244;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.732462;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.738757;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.225450;1.000000;,
  0.000000;1.000000;,
  0.000000;0.732462;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.738757;,
  1.000000;1.000000;,
  0.779854;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.225450;,
  0.000000;0.220146;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
