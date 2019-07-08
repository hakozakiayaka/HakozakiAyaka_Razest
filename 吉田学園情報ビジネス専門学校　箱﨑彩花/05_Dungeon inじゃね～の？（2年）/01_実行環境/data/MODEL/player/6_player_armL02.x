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
 157;
 1.10834;-0.84035;-1.07578;,
 0.80131;-0.97328;-1.20872;,
 0.83733;-0.56934;-1.45315;,
 1.24128;-0.53331;-1.20872;,
 0.35362;-1.03890;-1.27433;,
 0.35362;-0.60535;-1.53548;,
 0.35362;-0.08562;-1.62296;,
 0.87335;-0.08562;-1.53548;,
 1.30689;-0.08562;-1.27433;,
 -0.09408;-0.97328;-1.20872;,
 -0.13010;-0.56934;-1.45315;,
 -0.40111;-0.84035;-1.07578;,
 -0.53405;-0.53331;-1.20872;,
 -0.59966;-0.08562;-1.27433;,
 -0.16612;-0.08562;-1.53548;,
 -0.13010;0.39809;-1.45315;,
 0.35362;0.43411;-1.53548;,
 -0.53405;0.36207;-1.20872;,
 -0.40111;0.66910;-1.07578;,
 -0.09408;0.80204;-1.20872;,
 0.35362;0.86765;-1.27433;,
 0.83733;0.39809;-1.45315;,
 1.24128;0.36207;-1.20872;,
 0.80131;0.80204;-1.20872;,
 1.10834;0.66910;-1.07578;,
 0.83733;1.04647;-0.80477;,
 1.24128;0.80204;-0.76875;,
 0.35362;1.12880;-0.84079;,
 0.35362;1.21628;-0.32106;,
 0.87335;1.12880;-0.32106;,
 1.30689;0.86765;-0.32106;,
 -0.13010;1.04647;-0.80477;,
 -0.53405;0.80204;-0.76875;,
 -0.59966;0.86765;-0.32106;,
 -0.16612;1.12880;-0.32106;,
 -0.13010;1.04647;0.16265;,
 0.35362;1.12880;0.19868;,
 -0.53405;0.80204;0.12663;,
 -0.40111;0.66910;0.43367;,
 -0.09408;0.80204;0.56660;,
 0.35362;0.86765;0.63221;,
 0.83733;1.04647;0.16265;,
 1.24128;0.80204;0.12663;,
 0.80131;0.80204;0.56660;,
 1.10834;0.66910;0.43367;,
 0.83733;0.39809;0.81103;,
 1.24128;0.36207;0.56660;,
 0.35362;0.43411;0.89337;,
 0.35362;-0.08562;0.98085;,
 0.87335;-0.08562;0.89337;,
 1.30689;-0.08562;0.63221;,
 -0.13010;0.39809;0.81103;,
 -0.53405;0.36207;0.56660;,
 -0.59966;-0.08562;0.63221;,
 -0.16612;-0.08562;0.89337;,
 -0.13010;-0.56934;0.81103;,
 0.35362;-0.60535;0.89337;,
 -0.53405;-0.53331;0.56660;,
 -0.40111;-0.84035;0.43367;,
 -0.09408;-0.97328;0.56660;,
 0.35362;-1.03890;0.63221;,
 0.83733;-0.56934;0.81103;,
 1.24128;-0.53331;0.56660;,
 0.80131;-0.97328;0.56660;,
 1.10834;-0.84035;0.43367;,
 0.83733;-1.21771;0.16265;,
 1.24128;-0.97328;0.12663;,
 0.35362;-1.30005;0.19868;,
 0.35362;-1.38753;-0.32106;,
 0.87335;-1.30005;-0.32106;,
 1.30689;-1.03890;-0.32106;,
 -0.13010;-1.21771;0.16265;,
 -0.53405;-0.97328;0.12663;,
 -0.59966;-1.03890;-0.32106;,
 -0.16612;-1.30005;-0.32106;,
 -0.13010;-1.21771;-0.80477;,
 0.35362;-1.30005;-0.84079;,
 -0.53405;-0.97328;-0.76875;,
 -0.40111;-0.84035;-1.07578;,
 -0.09408;-0.97328;-1.20872;,
 0.35362;-1.03890;-1.27433;,
 0.83733;-1.21771;-0.80477;,
 1.24128;-0.97328;-0.76875;,
 0.80131;-0.97328;-1.20872;,
 1.10834;-0.84035;-1.07578;,
 -0.53405;-0.97328;-0.76875;,
 -0.77847;-0.56934;-0.80477;,
 -0.59966;-1.03890;-0.32106;,
 -0.86081;-0.60535;-0.32106;,
 -0.94829;-0.08562;-0.32106;,
 -0.86081;-0.08562;-0.84079;,
 -0.53405;-0.97328;0.12663;,
 -0.77847;-0.56934;0.16265;,
 -0.40111;-0.84035;0.43367;,
 -0.53405;-0.53331;0.56660;,
 -0.59966;-0.08562;0.63221;,
 -0.86081;-0.08562;0.19868;,
 -0.77847;0.39809;0.16265;,
 -0.86081;0.43411;-0.32106;,
 -0.53405;0.36207;0.56660;,
 -0.40111;0.66910;0.43367;,
 -0.53405;0.80204;0.12663;,
 -0.59966;0.86765;-0.32106;,
 -0.77847;0.39809;-0.80477;,
 -0.53405;0.80204;-0.76875;,
 1.10834;-0.84035;0.43367;,
 1.24128;-0.97328;0.12663;,
 1.48571;-0.56934;0.16265;,
 1.24128;-0.53331;0.56660;,
 1.30689;-1.03890;-0.32106;,
 1.56804;-0.60535;-0.32106;,
 1.65552;-0.08562;-0.32106;,
 1.56804;-0.08562;0.19868;,
 1.30689;-0.08562;0.63221;,
 1.24128;-0.97328;-0.76875;,
 1.48571;-0.56934;-0.80477;,
 1.56804;-0.08562;-0.84079;,
 1.48571;0.39809;-0.80477;,
 1.56804;0.43411;-0.32106;,
 1.24128;0.80204;-0.76875;,
 1.30689;0.86765;-0.32106;,
 1.48571;0.39809;0.16265;,
 1.24128;0.36207;0.56660;,
 1.24128;0.80204;0.12663;,
 1.10834;0.66910;0.43367;,
 4.48255;-0.11415;-2.21690;,
 0.57194;-0.14138;-1.87853;,
 0.57194;0.57489;-2.03476;,
 4.51249;0.73269;-2.25978;,
 4.48211;-1.46430;-1.43358;,
 4.49126;-1.43048;-1.12769;,
 0.57194;-1.38239;-0.78758;,
 0.57194;-1.39066;-1.06752;,
 0.57194;-1.22888;-1.34842;,
 4.47550;-1.30575;-1.72199;,
 0.57194;1.11015;0.58551;,
 0.57194;0.61710;1.29455;,
 4.57107;0.74580;1.27174;,
 4.57859;1.16725;0.69264;,
 0.57194;1.06401;-1.21756;,
 0.57194;1.41900;-0.26215;,
 4.58205;1.57740;-0.37596;,
 4.54861;1.22267;-1.45235;,
 0.57194;-1.21958;0.47503;,
 0.57194;-1.36538;-0.21196;,
 4.50396;-1.35231;-0.44047;,
 4.51168;-1.12662;0.37028;,
 0.57194;0.83118;-1.70424;,
 4.53007;0.99739;-1.93179;,
 4.58205;1.57740;-0.37596;,
 0.57194;1.41900;-0.26215;,
 4.50396;-1.35231;-0.44047;,
 0.57194;-1.36538;-0.21196;,
 0.57194;-0.72701;-1.63122;,
 4.47573;-0.76482;-1.99876;,
 0.57194;-0.31986;1.19381;,
 4.53919;-0.18997;1.15782;;
 
 134;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;2,5,6,7;,
 4;3,2,7,8;,
 4;4,9,10,5;,
 4;9,11,12,10;,
 4;10,12,13,14;,
 4;5,10,14,6;,
 4;6,14,15,16;,
 4;14,13,17,15;,
 4;15,17,18,19;,
 4;16,15,19,20;,
 4;8,7,21,22;,
 4;7,6,16,21;,
 4;21,16,20,23;,
 4;22,21,23,24;,
 4;24,23,25,26;,
 4;23,20,27,25;,
 4;25,27,28,29;,
 4;26,25,29,30;,
 4;20,19,31,27;,
 4;19,18,32,31;,
 4;31,32,33,34;,
 4;27,31,34,28;,
 4;28,34,35,36;,
 4;34,33,37,35;,
 4;35,37,38,39;,
 4;36,35,39,40;,
 4;30,29,41,42;,
 4;29,28,36,41;,
 4;41,36,40,43;,
 4;42,41,43,44;,
 4;44,43,45,46;,
 4;43,40,47,45;,
 4;45,47,48,49;,
 4;46,45,49,50;,
 4;40,39,51,47;,
 4;39,38,52,51;,
 4;51,52,53,54;,
 4;47,51,54,48;,
 4;48,54,55,56;,
 4;54,53,57,55;,
 4;55,57,58,59;,
 4;56,55,59,60;,
 4;50,49,61,62;,
 4;49,48,56,61;,
 4;61,56,60,63;,
 4;62,61,63,64;,
 4;64,63,65,66;,
 4;63,60,67,65;,
 4;65,67,68,69;,
 4;66,65,69,70;,
 4;60,59,71,67;,
 4;59,58,72,71;,
 4;71,72,73,74;,
 4;67,71,74,68;,
 4;68,74,75,76;,
 4;74,73,77,75;,
 4;75,77,78,79;,
 4;76,75,79,80;,
 4;70,69,81,82;,
 4;69,68,76,81;,
 4;81,76,80,83;,
 4;82,81,83,84;,
 4;11,85,86,12;,
 4;85,87,88,86;,
 4;86,88,89,90;,
 4;12,86,90,13;,
 4;87,91,92,88;,
 4;91,93,94,92;,
 4;92,94,95,96;,
 4;88,92,96,89;,
 4;89,96,97,98;,
 4;96,95,99,97;,
 4;97,99,100,101;,
 4;98,97,101,102;,
 4;13,90,103,17;,
 4;90,89,98,103;,
 4;103,98,102,104;,
 4;17,103,104,18;,
 4;105,106,107,108;,
 4;106,109,110,107;,
 4;107,110,111,112;,
 4;108,107,112,113;,
 4;109,114,115,110;,
 4;114,0,3,115;,
 4;115,3,8,116;,
 4;110,115,116,111;,
 4;111,116,117,118;,
 4;116,8,22,117;,
 4;117,22,24,119;,
 4;118,117,119,120;,
 4;113,112,121,122;,
 4;112,111,118,121;,
 4;121,118,120,123;,
 4;122,121,123,124;,
 4;125,126,127,128;,
 4;129,130,131,132;,
 4;129,132,133,134;,
 4;135,136,137,138;,
 4;139,140,141,142;,
 4;143,144,145,146;,
 4;128,127,147,148;,
 4;147,139,142,148;,
 4;149,150,135,138;,
 4;151,152,131,130;,
 4;134,133,153,154;,
 4;153,126,125,154;,
 4;136,155,156,137;,
 4;156,155,143,146;,
 3;128,148,125;,
 3;125,148,154;,
 3;154,148,134;,
 3;148,142,134;,
 3;134,142,129;,
 3;129,142,130;,
 3;142,149,130;,
 3;130,149,151;,
 3;151,149,146;,
 3;149,138,146;,
 3;146,138,156;,
 3;138,137,156;,
 3;136,135,155;,
 3;155,135,143;,
 3;135,140,143;,
 3;143,140,144;,
 3;140,139,144;,
 3;144,139,131;,
 3;131,139,132;,
 3;139,147,132;,
 3;132,147,133;,
 3;133,147,153;,
 3;147,127,153;,
 3;127,126,153;;
 
 MeshMaterialList {
  1;
  134;
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
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/player.png";
   }
  }
 }
 MeshNormals {
  128;
  0.577349;-0.577354;-0.577348;,
  -0.577352;-0.577352;-0.577347;,
  0.577351;0.577350;-0.577350;,
  -0.577353;0.577349;-0.577348;,
  0.577350;0.577350;0.577351;,
  -0.577353;0.577349;0.577349;,
  0.577349;-0.577353;0.577349;,
  -0.577351;-0.577352;0.577348;,
  -0.707110;0.000001;-0.707104;,
  0.000002;0.707107;-0.707107;,
  0.707107;0.707107;0.000000;,
  -0.707110;0.707104;0.000000;,
  0.000002;0.707108;0.707106;,
  0.707108;0.000001;0.707105;,
  -0.707111;0.000001;0.707103;,
  0.000002;-0.707108;0.707106;,
  0.707107;-0.707106;0.000000;,
  -0.707110;-0.707104;0.000000;,
  0.000002;-0.707106;-0.707107;,
  0.707107;0.000001;-0.707107;,
  0.000002;0.000001;-1.000000;,
  0.000002;1.000000;-0.000001;,
  0.000002;0.000001;1.000000;,
  0.000002;-1.000000;-0.000001;,
  -1.000000;0.000001;-0.000001;,
  1.000000;0.000001;-0.000001;,
  0.000002;-0.353809;-0.935317;,
  0.353810;0.000001;-0.935317;,
  -0.354075;-0.661300;-0.661297;,
  -0.661302;-0.354074;-0.661295;,
  -0.353808;0.000001;-0.935318;,
  0.000002;0.353810;-0.935317;,
  -0.661302;0.354075;-0.661295;,
  -0.354072;0.661299;-0.661299;,
  0.661299;0.354075;-0.661298;,
  0.354075;0.661298;-0.661298;,
  0.661299;0.661298;-0.354074;,
  0.000002;0.935317;-0.353810;,
  0.353811;0.935317;-0.000000;,
  -0.661302;0.661295;-0.354075;,
  -0.353809;0.935318;-0.000000;,
  0.000002;0.935317;0.353812;,
  -0.661302;0.661296;0.354072;,
  -0.354073;0.661299;0.661299;,
  0.661299;0.661299;0.354072;,
  0.354075;0.661298;0.661298;,
  0.661298;0.354075;0.661298;,
  0.000002;0.353819;0.935314;,
  0.353819;0.000001;0.935314;,
  -0.661302;0.354076;0.661295;,
  -0.353817;0.000001;0.935315;,
  0.000002;-0.353818;0.935314;,
  -0.661302;-0.354074;0.661295;,
  -0.354075;-0.661300;0.661296;,
  0.661299;-0.354074;0.661298;,
  0.354078;-0.661299;0.661296;,
  0.661297;-0.661300;0.354075;,
  0.000002;-0.935315;0.353817;,
  0.353815;-0.935315;-0.000000;,
  -0.661300;-0.661297;0.354075;,
  -0.353813;-0.935316;-0.000000;,
  0.000002;-0.935315;-0.353815;,
  -0.661299;-0.661296;-0.354077;,
  0.661296;-0.661299;-0.354077;,
  -0.935317;-0.353810;-0.000000;,
  -0.935317;0.000001;-0.353810;,
  -0.935316;0.000001;0.353812;,
  -0.935317;0.353811;-0.000000;,
  0.935317;-0.353810;-0.000000;,
  0.935317;0.000001;0.353812;,
  0.935317;0.000001;-0.353810;,
  0.935317;0.353811;-0.000000;,
  0.354077;-0.661300;-0.661296;,
  0.661299;-0.354074;-0.661298;,
  0.353226;-0.353225;-0.866293;,
  -0.353224;-0.353225;-0.866293;,
  -0.353224;0.353226;-0.866293;,
  0.353226;0.353226;-0.866292;,
  0.353226;0.866292;-0.353226;,
  -0.353224;0.866293;-0.353226;,
  -0.353225;0.866293;0.353226;,
  0.353227;0.866292;0.353225;,
  0.353230;0.353230;0.866289;,
  -0.353228;0.353231;0.866290;,
  -0.353228;-0.353230;0.866290;,
  0.353230;-0.353229;0.866289;,
  0.353230;-0.866290;0.353229;,
  -0.353228;-0.866291;0.353229;,
  -0.353228;-0.866290;-0.353230;,
  0.353230;-0.866289;-0.353229;,
  -0.866293;-0.353225;-0.353226;,
  -0.866293;-0.353225;0.353225;,
  -0.866293;0.353226;0.353225;,
  -0.866293;0.353226;-0.353225;,
  0.866293;-0.353226;0.353226;,
  0.866293;-0.353226;-0.353226;,
  0.866292;0.353227;-0.353226;,
  0.866292;0.353227;0.353225;,
  -0.079818;-0.698362;-0.711281;,
  -0.025202;0.814649;0.579406;,
  -0.040497;0.999119;0.011017;,
  -0.078558;0.375037;-0.923675;,
  0.012558;-0.987807;0.155173;,
  -0.056756;0.923827;-0.378580;,
  -0.025123;0.882964;0.468768;,
  -0.003865;-0.997495;0.070628;,
  -0.077540;-0.243080;-0.966902;,
  0.022303;-0.389815;0.920623;,
  0.029221;-0.845820;0.532668;,
  -0.065084;0.848239;-0.525600;,
  -0.087796;-0.412588;-0.906677;,
  -0.037640;-0.975051;-0.218768;,
  0.011040;-0.114031;0.993416;,
  0.999043;-0.036540;-0.024053;,
  0.998748;-0.030006;-0.040029;,
  0.998697;-0.032629;-0.039245;,
  0.998084;-0.028693;-0.054825;,
  0.998869;-0.026582;-0.039418;,
  0.999285;-0.025101;-0.028290;,
  0.999180;-0.024952;-0.031882;,
  0.999443;-0.025214;-0.021872;,
  0.999580;-0.026354;-0.012036;,
  0.999611;-0.026450;-0.008797;,
  0.999604;-0.027937;-0.003316;,
  0.999531;-0.029980;-0.006226;,
  0.999506;-0.030922;-0.005565;,
  0.999406;-0.032727;-0.010840;,
  -1.000000;0.000000;0.000000;;
  134;
  4;0,72,74,73;,
  4;72,18,26,74;,
  4;74,26,20,27;,
  4;73,74,27,19;,
  4;18,28,75,26;,
  4;28,1,29,75;,
  4;75,29,8,30;,
  4;26,75,30,20;,
  4;20,30,76,31;,
  4;30,8,32,76;,
  4;76,32,3,33;,
  4;31,76,33,9;,
  4;19,27,77,34;,
  4;27,20,31,77;,
  4;77,31,9,35;,
  4;34,77,35,2;,
  4;2,35,78,36;,
  4;35,9,37,78;,
  4;78,37,21,38;,
  4;36,78,38,10;,
  4;9,33,79,37;,
  4;33,3,39,79;,
  4;79,39,11,40;,
  4;37,79,40,21;,
  4;21,40,80,41;,
  4;40,11,42,80;,
  4;80,42,5,43;,
  4;41,80,43,12;,
  4;10,38,81,44;,
  4;38,21,41,81;,
  4;81,41,12,45;,
  4;44,81,45,4;,
  4;4,45,82,46;,
  4;45,12,47,82;,
  4;82,47,22,48;,
  4;46,82,48,13;,
  4;12,43,83,47;,
  4;43,5,49,83;,
  4;83,49,14,50;,
  4;47,83,50,22;,
  4;22,50,84,51;,
  4;50,14,52,84;,
  4;84,52,7,53;,
  4;51,84,53,15;,
  4;13,48,85,54;,
  4;48,22,51,85;,
  4;85,51,15,55;,
  4;54,85,55,6;,
  4;6,55,86,56;,
  4;55,15,57,86;,
  4;86,57,23,58;,
  4;56,86,58,16;,
  4;15,53,87,57;,
  4;53,7,59,87;,
  4;87,59,17,60;,
  4;57,87,60,23;,
  4;23,60,88,61;,
  4;60,17,62,88;,
  4;88,62,1,28;,
  4;61,88,28,18;,
  4;16,58,89,63;,
  4;58,23,61,89;,
  4;89,61,18,72;,
  4;63,89,72,0;,
  4;1,62,90,29;,
  4;62,17,64,90;,
  4;90,64,24,65;,
  4;29,90,65,8;,
  4;17,59,91,64;,
  4;59,7,52,91;,
  4;91,52,14,66;,
  4;64,91,66,24;,
  4;24,66,92,67;,
  4;66,14,49,92;,
  4;92,49,5,42;,
  4;67,92,42,11;,
  4;8,65,93,32;,
  4;65,24,67,93;,
  4;93,67,11,39;,
  4;32,93,39,3;,
  4;6,56,94,54;,
  4;56,16,68,94;,
  4;94,68,25,69;,
  4;54,94,69,13;,
  4;16,63,95,68;,
  4;63,0,73,95;,
  4;95,73,19,70;,
  4;68,95,70,25;,
  4;25,70,96,71;,
  4;70,19,34,96;,
  4;96,34,2,36;,
  4;71,96,36,10;,
  4;13,69,97,46;,
  4;69,25,71,97;,
  4;97,71,10,44;,
  4;46,97,44,4;,
  4;106,106,101,101;,
  4;111,105,105,111;,
  4;111,111,98,98;,
  4;104,99,99,104;,
  4;103,100,100,103;,
  4;108,102,102,108;,
  4;101,101,109,109;,
  4;109,103,103,109;,
  4;100,100,104,104;,
  4;102,102,105,105;,
  4;98,98,110,110;,
  4;110,106,106,110;,
  4;112,107,107,112;,
  4;107,107,108,108;,
  3;113,114,115;,
  3;115,114,116;,
  3;116,114,117;,
  3;114,118,117;,
  3;117,118,119;,
  3;119,118,120;,
  3;118,121,120;,
  3;120,121,122;,
  3;122,121,123;,
  3;121,124,123;,
  3;123,124,125;,
  3;124,126,125;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;,
  3;127,127,127;;
 }
 MeshTextureCoords {
  157;
  0.360920;0.198450;,
  0.373180;0.198450;,
  0.373180;0.193780;,
  0.360920;0.193780;,
  0.385440;0.198450;,
  0.385440;0.193780;,
  0.385440;0.189100;,
  0.373180;0.189100;,
  0.360920;0.189100;,
  0.397700;0.198450;,
  0.397700;0.193780;,
  0.409960;0.198450;,
  0.409960;0.193780;,
  0.409960;0.189100;,
  0.397700;0.189100;,
  0.397700;0.184420;,
  0.385440;0.184420;,
  0.409960;0.184420;,
  0.409960;0.179740;,
  0.397700;0.179740;,
  0.385440;0.179740;,
  0.373180;0.184420;,
  0.360920;0.184420;,
  0.373180;0.179740;,
  0.360920;0.179740;,
  0.373180;0.175060;,
  0.360920;0.175060;,
  0.385440;0.175060;,
  0.385440;0.170380;,
  0.373180;0.170380;,
  0.360920;0.170380;,
  0.397700;0.175060;,
  0.409960;0.175060;,
  0.409960;0.170380;,
  0.397700;0.170380;,
  0.397700;0.165710;,
  0.385440;0.165710;,
  0.409960;0.165710;,
  0.409960;0.161030;,
  0.397700;0.161030;,
  0.385440;0.161030;,
  0.373180;0.165710;,
  0.360920;0.165710;,
  0.373180;0.161030;,
  0.360920;0.161030;,
  0.373180;0.156350;,
  0.360920;0.156350;,
  0.385440;0.156350;,
  0.385440;0.151670;,
  0.373180;0.151670;,
  0.360920;0.151670;,
  0.397700;0.156350;,
  0.409960;0.156350;,
  0.409960;0.151670;,
  0.397700;0.151670;,
  0.397700;0.146990;,
  0.385440;0.146990;,
  0.409960;0.146990;,
  0.409960;0.142310;,
  0.397700;0.142310;,
  0.385440;0.142310;,
  0.373180;0.146990;,
  0.360920;0.146990;,
  0.373180;0.142310;,
  0.360920;0.142310;,
  0.373180;0.137630;,
  0.360920;0.137630;,
  0.385440;0.137630;,
  0.385440;0.132960;,
  0.373180;0.132960;,
  0.360920;0.132960;,
  0.397700;0.137630;,
  0.409960;0.137630;,
  0.409960;0.132960;,
  0.397700;0.132960;,
  0.397700;0.128280;,
  0.385440;0.128280;,
  0.409960;0.128280;,
  0.409960;0.123600;,
  0.397700;0.123600;,
  0.385440;0.123600;,
  0.373180;0.128280;,
  0.360920;0.128280;,
  0.373180;0.123600;,
  0.360920;0.123600;,
  0.422220;0.198450;,
  0.422220;0.193780;,
  0.434470;0.198450;,
  0.434470;0.193780;,
  0.434470;0.189100;,
  0.422220;0.189100;,
  0.446730;0.198450;,
  0.446730;0.193780;,
  0.458990;0.198450;,
  0.458990;0.193780;,
  0.458990;0.189100;,
  0.446730;0.189100;,
  0.446730;0.184420;,
  0.434470;0.184420;,
  0.458990;0.184420;,
  0.458990;0.179740;,
  0.446730;0.179740;,
  0.434470;0.179740;,
  0.422220;0.184420;,
  0.422220;0.179740;,
  0.311890;0.198450;,
  0.324150;0.198450;,
  0.324150;0.193780;,
  0.311890;0.193780;,
  0.336410;0.198450;,
  0.336410;0.193780;,
  0.336410;0.189100;,
  0.324150;0.189100;,
  0.311890;0.189100;,
  0.348660;0.198450;,
  0.348660;0.193780;,
  0.348660;0.189100;,
  0.348660;0.184420;,
  0.336410;0.184420;,
  0.348660;0.179740;,
  0.336410;0.179740;,
  0.324150;0.184420;,
  0.311890;0.184420;,
  0.324150;0.179740;,
  0.311890;0.179740;,
  0.805730;0.753710;,
  0.849350;0.755100;,
  0.849440;0.746330;,
  0.805580;0.742690;,
  0.807250;0.774430;,
  0.807850;0.778240;,
  0.850890;0.776940;,
  0.850390;0.773560;,
  0.849930;0.769650;,
  0.806530;0.770350;,
  0.663740;0.828890;,
  0.663560;0.839120;,
  0.707410;0.838500;,
  0.707220;0.829680;,
  0.850870;0.734880;,
  0.852650;0.722480;,
  0.810160;0.716930;,
  0.807430;0.730680;,
  0.662570;0.864210;,
  0.662640;0.872670;,
  0.704690;0.875210;,
  0.704830;0.865030;,
  0.849990;0.741360;,
  0.806280;0.737300;,
  0.706320;0.815780;,
  0.663670;0.818130;,
  0.809290;0.786660;,
  0.851910;0.783940;,
  0.849550;0.762720;,
  0.806070;0.762580;,
  0.663030;0.850350;,
  0.706160;0.850100;;
 }
}
