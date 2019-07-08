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
 196;
 -19.55619;81.77045;-15.15026;,
 18.62920;81.77045;-15.15026;,
 18.62920;9.46807;-15.15026;,
 -19.55619;9.46807;-15.15026;,
 18.62920;81.77045;-15.15026;,
 18.62920;81.77045;15.35847;,
 18.62920;9.46807;15.35847;,
 18.62920;9.46807;-15.15026;,
 18.62920;81.77045;15.35847;,
 -19.55619;81.77045;15.35847;,
 -19.55619;9.46807;15.35847;,
 18.62920;9.46807;15.35847;,
 -19.55619;81.77045;15.35847;,
 -19.55619;81.77045;-15.15026;,
 -19.55619;9.46807;-15.15026;,
 -19.55619;9.46807;15.35847;,
 18.62920;81.77045;-15.15026;,
 -19.55619;81.77045;-15.15026;,
 -19.55619;9.46807;-15.15026;,
 18.62920;9.46807;-15.15026;,
 8.62601;4.49881;-14.26409;,
 19.06652;4.49881;-14.26409;,
 19.06652;-0.08601;-14.26409;,
 8.62601;-0.08601;-14.26409;,
 19.06652;4.49881;-14.26409;,
 19.06652;4.49881;14.47227;,
 19.06652;-0.08601;14.47227;,
 19.06652;-0.08601;-14.26409;,
 19.06652;4.49881;14.47227;,
 8.62601;4.49881;14.47227;,
 8.62601;-0.08601;14.47227;,
 19.06652;-0.08601;14.47227;,
 8.62601;4.49881;14.47227;,
 8.62601;4.49881;-14.26409;,
 8.62601;-0.08601;-14.26409;,
 8.62601;-0.08601;14.47227;,
 19.06652;4.49881;-14.26409;,
 8.62601;4.49881;-14.26409;,
 8.62601;-0.08601;-14.26409;,
 19.06652;-0.08601;-14.26409;,
 -20.27362;4.70168;-14.26409;,
 -9.83312;4.70168;-14.26409;,
 -9.83312;-0.28881;-14.26409;,
 -20.27362;-0.28881;-14.26409;,
 -9.83312;4.70168;-14.26409;,
 -9.83312;4.70168;14.47227;,
 -9.83312;-0.28881;14.47227;,
 -9.83312;-0.28881;-14.26409;,
 -9.83312;4.70168;14.47227;,
 -20.27362;4.70168;14.47227;,
 -20.27362;-0.28881;14.47227;,
 -9.83312;-0.28881;14.47227;,
 -20.27362;4.70168;14.47227;,
 -20.27362;4.70168;-14.26409;,
 -20.27362;-0.28881;-14.26409;,
 -20.27362;-0.28881;14.47227;,
 -9.83312;4.70168;-14.26409;,
 -20.27362;4.70168;-14.26409;,
 -20.27362;-0.28881;-14.26409;,
 -9.83312;-0.28881;-14.26409;,
 -15.83053;10.93135;4.35467;,
 -14.10099;10.93135;5.23362;,
 -14.10099;4.46320;5.23362;,
 -15.83053;4.46320;4.35467;,
 -13.38458;10.93135;7.35561;,
 -13.38458;4.46320;7.35561;,
 -14.10099;10.93135;9.47760;,
 -14.10099;4.46320;9.47760;,
 -15.83053;10.93135;10.35658;,
 -15.83053;4.46320;10.35658;,
 -17.56008;10.93135;9.47760;,
 -17.56008;4.46320;9.47760;,
 -18.27650;10.93135;7.35561;,
 -18.27650;4.46320;7.35561;,
 -17.56008;10.93135;5.23362;,
 -17.56008;4.46320;5.23362;,
 -15.83053;10.93135;4.35467;,
 -15.83053;4.46320;4.35467;,
 -15.83053;10.93135;7.35561;,
 -15.83053;10.93135;7.35561;,
 -15.83053;10.93135;7.35561;,
 -15.83053;10.93135;7.35561;,
 -15.83053;10.93135;7.35561;,
 -15.83053;10.93135;7.35561;,
 -15.83053;10.93135;7.35561;,
 -15.83053;10.93135;7.35561;,
 -15.83053;4.46320;7.35561;,
 -15.83053;4.46320;7.35561;,
 -15.83053;4.46320;7.35561;,
 -15.83053;4.46320;7.35561;,
 -15.83053;4.46320;7.35561;,
 -15.83053;4.46320;7.35561;,
 -15.83053;4.46320;7.35561;,
 -15.83053;4.46320;7.35561;,
 -15.83053;10.93135;-9.75422;,
 -14.10099;10.93135;-8.87524;,
 -14.10099;4.46320;-8.87524;,
 -15.83053;4.46320;-9.75422;,
 -13.38458;10.93135;-6.75325;,
 -13.38458;4.46320;-6.75325;,
 -14.10099;10.93135;-4.63129;,
 -14.10099;4.46320;-4.63129;,
 -15.83053;10.93135;-3.75231;,
 -15.83053;4.46320;-3.75231;,
 -17.56008;10.93135;-4.63129;,
 -17.56008;4.46320;-4.63129;,
 -18.27650;10.93135;-6.75325;,
 -18.27650;4.46320;-6.75325;,
 -17.56008;10.93135;-8.87524;,
 -17.56008;4.46320;-8.87524;,
 -15.83053;10.93135;-9.75422;,
 -15.83053;4.46320;-9.75422;,
 -15.83053;10.93135;-6.75325;,
 -15.83053;10.93135;-6.75325;,
 -15.83053;10.93135;-6.75325;,
 -15.83053;10.93135;-6.75325;,
 -15.83053;10.93135;-6.75325;,
 -15.83053;10.93135;-6.75325;,
 -15.83053;10.93135;-6.75325;,
 -15.83053;10.93135;-6.75325;,
 -15.83053;4.46320;-6.75325;,
 -15.83053;4.46320;-6.75325;,
 -15.83053;4.46320;-6.75325;,
 -15.83053;4.46320;-6.75325;,
 -15.83053;4.46320;-6.75325;,
 -15.83053;4.46320;-6.75325;,
 -15.83053;4.46320;-6.75325;,
 -15.83053;4.46320;-6.75325;,
 14.17997;10.93135;4.35467;,
 15.90950;10.93135;5.23362;,
 15.90950;4.46320;5.23362;,
 14.17997;4.46320;4.35467;,
 16.62593;10.93135;7.35561;,
 16.62593;4.46320;7.35561;,
 15.90950;10.93135;9.47760;,
 15.90950;4.46320;9.47760;,
 14.17997;10.93135;10.35658;,
 14.17997;4.46320;10.35658;,
 12.45040;10.93135;9.47760;,
 12.45040;4.46320;9.47760;,
 11.73399;10.93135;7.35561;,
 11.73399;4.46320;7.35561;,
 12.45040;10.93135;5.23362;,
 12.45040;4.46320;5.23362;,
 14.17997;10.93135;4.35467;,
 14.17997;4.46320;4.35467;,
 14.17997;10.93135;7.35561;,
 14.17997;10.93135;7.35561;,
 14.17997;10.93135;7.35561;,
 14.17997;10.93135;7.35561;,
 14.17997;10.93135;7.35561;,
 14.17997;10.93135;7.35561;,
 14.17997;10.93135;7.35561;,
 14.17997;10.93135;7.35561;,
 14.17997;4.46320;7.35561;,
 14.17997;4.46320;7.35561;,
 14.17997;4.46320;7.35561;,
 14.17997;4.46320;7.35561;,
 14.17997;4.46320;7.35561;,
 14.17997;4.46320;7.35561;,
 14.17997;4.46320;7.35561;,
 14.17997;4.46320;7.35561;,
 14.17997;10.93135;-8.65268;,
 15.90950;10.93135;-7.77372;,
 15.90950;4.46320;-7.77372;,
 14.17997;4.46320;-8.65268;,
 16.62593;10.93135;-5.65174;,
 16.62593;4.46320;-5.65174;,
 15.90950;10.93135;-3.52975;,
 15.90950;4.46320;-3.52975;,
 14.17997;10.93135;-2.65079;,
 14.17997;4.46320;-2.65079;,
 12.45040;10.93135;-3.52975;,
 12.45040;4.46320;-3.52975;,
 11.73399;10.93135;-5.65174;,
 11.73399;4.46320;-5.65174;,
 12.45040;10.93135;-7.77372;,
 12.45040;4.46320;-7.77372;,
 14.17997;10.93135;-8.65268;,
 14.17997;4.46320;-8.65268;,
 14.17997;10.93135;-5.65174;,
 14.17997;10.93135;-5.65174;,
 14.17997;10.93135;-5.65174;,
 14.17997;10.93135;-5.65174;,
 14.17997;10.93135;-5.65174;,
 14.17997;10.93135;-5.65174;,
 14.17997;10.93135;-5.65174;,
 14.17997;10.93135;-5.65174;,
 14.17997;4.46320;-5.65174;,
 14.17997;4.46320;-5.65174;,
 14.17997;4.46320;-5.65174;,
 14.17997;4.46320;-5.65174;,
 14.17997;4.46320;-5.65174;,
 14.17997;4.46320;-5.65174;,
 14.17997;4.46320;-5.65174;,
 14.17997;4.46320;-5.65174;;
 
 114;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;61,64,65,62;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;72,74,75,73;,
 4;74,76,77,75;,
 3;78,61,60;,
 3;79,64,61;,
 3;80,66,64;,
 3;81,68,66;,
 3;82,70,68;,
 3;83,72,70;,
 3;84,74,72;,
 3;85,76,74;,
 3;86,63,62;,
 3;87,62,65;,
 3;88,65,67;,
 3;89,67,69;,
 3;90,69,71;,
 3;91,71,73;,
 3;92,73,75;,
 3;93,75,77;,
 4;94,95,96,97;,
 4;95,98,99,96;,
 4;98,100,101,99;,
 4;100,102,103,101;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,108,109,107;,
 4;108,110,111,109;,
 3;112,95,94;,
 3;113,98,95;,
 3;114,100,98;,
 3;115,102,100;,
 3;116,104,102;,
 3;117,106,104;,
 3;118,108,106;,
 3;119,110,108;,
 3;120,97,96;,
 3;121,96,99;,
 3;122,99,101;,
 3;123,101,103;,
 3;124,103,105;,
 3;125,105,107;,
 3;126,107,109;,
 3;127,109,111;,
 4;128,129,130,131;,
 4;129,132,133,130;,
 4;132,134,135,133;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,144,145,143;,
 3;146,129,128;,
 3;147,132,129;,
 3;148,134,132;,
 3;149,136,134;,
 3;150,138,136;,
 3;151,140,138;,
 3;152,142,140;,
 3;153,144,142;,
 3;154,131,130;,
 3;155,130,133;,
 3;156,133,135;,
 3;157,135,137;,
 3;158,137,139;,
 3;159,139,141;,
 3;160,141,143;,
 3;161,143,145;,
 4;162,163,164,165;,
 4;163,166,167,164;,
 4;166,168,169,167;,
 4;168,170,171,169;,
 4;170,172,173,171;,
 4;172,174,175,173;,
 4;174,176,177,175;,
 4;176,178,179,177;,
 3;180,163,162;,
 3;181,166,163;,
 3;182,168,166;,
 3;183,170,168;,
 3;184,172,170;,
 3;185,174,172;,
 3;186,176,174;,
 3;187,178,176;,
 3;188,165,164;,
 3;189,164,167;,
 3;190,167,169;,
 3;191,169,171;,
 3;192,171,173;,
 3;193,173,175;,
 3;194,175,177;,
 3;195,177,179;;
 
 MeshMaterialList {
  3;
  114;
  0,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\th.jpg";
   }
  }
  Material {
   0.800000;0.000000;0.062745;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.454902;0.454902;0.454902;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  58;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000001;0.000000;-1.000000;,
  0.756336;0.000000;-0.654183;,
  1.000000;0.000000;0.000000;,
  0.756340;0.000000;0.654179;,
  -0.000001;0.000000;1.000000;,
  -0.756337;0.000000;0.654182;,
  -1.000000;0.000000;0.000000;,
  -0.756333;0.000000;-0.654187;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000001;0.000000;-1.000000;,
  0.756340;0.000000;-0.654178;,
  1.000000;0.000000;0.000001;,
  0.756339;0.000000;0.654180;,
  -0.000001;0.000000;1.000000;,
  -0.756336;0.000000;0.654183;,
  -1.000000;0.000000;0.000002;,
  -0.756337;0.000000;-0.654182;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000005;0.000000;-1.000000;,
  0.756335;0.000000;-0.654185;,
  1.000000;0.000000;0.000000;,
  0.756339;0.000000;0.654180;,
  0.000005;0.000000;1.000000;,
  -0.756337;0.000000;0.654182;,
  -1.000000;0.000000;0.000000;,
  -0.756333;0.000000;-0.654186;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000005;0.000000;-1.000000;,
  0.756335;0.000000;-0.654184;,
  1.000000;0.000000;-0.000000;,
  0.756335;0.000000;0.654184;,
  0.000005;0.000000;1.000000;,
  -0.756333;0.000000;0.654186;,
  -1.000000;0.000000;-0.000000;,
  -0.756333;0.000000;-0.654186;,
  0.000000;-1.000000;-0.000000;;
  114;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;19,20,20,19;,
  4;20,21,21,20;,
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;23,24,24,23;,
  4;24,25,25,24;,
  4;25,26,26,25;,
  4;26,19,19,26;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;18,18,18;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  3;27,27,27;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,35,35,34;,
  4;35,36,36,35;,
  4;36,29,29,36;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;28,28,28;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  3;37,37,37;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,39,39,46;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;56,49,49,56;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;;
 }
 MeshTextureCoords {
  196;
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
  0.937500;1.000000;;
 }
}
