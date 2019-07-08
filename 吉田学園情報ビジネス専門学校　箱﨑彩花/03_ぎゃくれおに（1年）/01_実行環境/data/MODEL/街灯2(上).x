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
 48;
 -12.49546;235.68323;-12.42546;,
 0.00000;235.68323;-18.45982;,
 0.00000;217.15340;-18.45982;,
 -11.03064;217.15340;-10.96064;,
 12.49546;235.68323;-12.42546;,
 11.03064;217.15340;-10.96064;,
 0.00000;198.62357;-18.45982;,
 -7.32797;198.62357;-7.25797;,
 7.32797;198.62357;-7.25797;,
 12.49546;235.68323;-12.42546;,
 18.52982;235.68323;0.07000;,
 18.52982;217.15340;0.07000;,
 11.03064;217.15340;-10.96064;,
 12.49546;235.68323;12.56546;,
 11.03064;217.15340;11.10064;,
 18.52982;198.62357;0.07000;,
 7.32797;198.62357;-7.25797;,
 7.32797;198.62357;7.39797;,
 12.49546;235.68323;12.56546;,
 0.00000;235.68323;18.59982;,
 0.00000;217.15340;18.59982;,
 11.03064;217.15340;11.10064;,
 -12.49546;235.68323;12.56546;,
 -11.03064;217.15340;11.10064;,
 0.00000;198.62357;18.59982;,
 7.32797;198.62357;7.39797;,
 -7.32797;198.62357;7.39797;,
 -12.49546;235.68323;12.56546;,
 -18.52982;235.68323;0.07000;,
 -18.52982;217.15340;0.07000;,
 -11.03064;217.15340;11.10064;,
 -12.49546;235.68323;-12.42546;,
 -11.03064;217.15340;-10.96064;,
 -18.52982;198.62357;0.07000;,
 -7.32797;198.62357;7.39797;,
 -7.32797;198.62357;-7.25797;,
 0.00000;251.94269;0.07000;,
 -18.52982;235.68323;0.07000;,
 18.52982;235.68323;0.07000;,
 0.00000;235.68323;-18.45982;,
 -12.49546;235.68323;-12.42546;,
 12.49546;235.68323;-12.42546;,
 -18.52982;198.62357;0.07000;,
 0.00000;198.80750;0.07000;,
 18.52982;198.62357;0.07000;,
 -7.32797;198.62357;-7.25797;,
 0.00000;198.62357;-18.45982;,
 7.32797;198.62357;-7.25797;;
 
 24;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;9,10,11,12;,
 4;10,13,14,11;,
 4;12,11,15,16;,
 4;11,14,17,15;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;21,20,24,25;,
 4;20,23,26,24;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;30,29,33,34;,
 4;29,32,35,33;,
 4;27,19,36,37;,
 4;19,13,38,36;,
 4;37,36,39,40;,
 4;36,38,41,39;,
 4;42,43,24,34;,
 4;43,44,17,24;,
 4;45,46,43,42;,
 4;46,47,44,43;;
 
 MeshMaterialList {
  2;
  24;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.420392;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.241600;0.241600;0.241600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  47;
  -0.687283;0.235124;-0.687283;,
  -0.544375;0.380212;-0.747727;,
  -0.703797;-0.096641;-0.703797;,
  -0.607617;-0.095848;-0.788425;,
  -0.700426;-0.137133;-0.700426;,
  -0.704061;-0.137131;-0.696773;,
  0.687283;0.235124;-0.687283;,
  0.747727;0.380212;-0.544375;,
  0.703797;-0.096641;-0.703797;,
  0.788425;-0.095848;-0.607617;,
  0.700426;-0.137133;-0.700426;,
  0.696773;-0.137131;-0.704061;,
  0.687283;0.235124;0.687283;,
  0.544375;0.380212;0.747727;,
  0.703797;-0.096641;0.703797;,
  0.607617;-0.095848;0.788425;,
  0.700426;-0.137133;0.700426;,
  0.704061;-0.137131;0.696773;,
  -0.687283;0.235124;0.687283;,
  -0.747727;0.380212;0.544375;,
  -0.703797;-0.096641;0.703797;,
  -0.788425;-0.095848;0.607617;,
  -0.700426;-0.137133;0.700426;,
  -0.696773;-0.137131;0.704061;,
  0.000000;0.838208;0.545350;,
  0.000000;-1.000000;0.000000;,
  0.544375;0.380212;-0.747727;,
  0.607617;-0.095848;-0.788425;,
  0.704061;-0.137131;-0.696773;,
  0.747727;0.380212;0.544375;,
  0.788425;-0.095848;0.607617;,
  0.696773;-0.137131;0.704061;,
  -0.544375;0.380212;0.747727;,
  -0.607617;-0.095848;0.788425;,
  -0.704061;-0.137131;0.696773;,
  -0.747727;0.380212;-0.544375;,
  -0.788425;-0.095848;-0.607617;,
  -0.696773;-0.137131;-0.704061;,
  0.000000;0.838208;-0.545350;,
  0.012549;-0.999921;0.000000;,
  0.000000;-0.999921;-0.012549;,
  0.012548;-0.999843;-0.012548;,
  -0.012549;-0.999921;0.000000;,
  -0.012548;-0.999843;-0.012548;,
  0.012548;-0.999843;0.012548;,
  0.000000;-0.999921;0.012549;,
  -0.012548;-0.999843;0.012548;;
  24;
  4;0,1,3,2;,
  4;26,6,8,27;,
  4;2,3,5,4;,
  4;27,8,10,28;,
  4;6,7,9,8;,
  4;29,12,14,30;,
  4;8,9,11,10;,
  4;30,14,16,31;,
  4;12,13,15,14;,
  4;32,18,20,33;,
  4;14,15,17,16;,
  4;33,20,22,34;,
  4;18,19,21,20;,
  4;35,0,2,36;,
  4;20,21,23,22;,
  4;36,2,4,37;,
  4;18,32,24,19;,
  4;13,12,29,24;,
  4;35,38,1,0;,
  4;38,7,6,26;,
  4;39,25,40,41;,
  4;25,42,43,40;,
  4;44,45,25,39;,
  4;45,46,42,25;;
 }
 MeshTextureCoords {
  48;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}
