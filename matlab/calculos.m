clc; clear all; close all;
%------------------------------------------Codificacion
%matriz de mensaje
m = [0 0 0 ;
     0 0 1 ;
     0 1 0 ;
     0 1 1 ;
     1 0 0 ;
     1 0 1 ;
     1 1 0 ;
     1 1 1 ];
%matriz identidad
I = eye(3);
%matriz de paridad
P = [ 1 1 1 ;
      1 0 1 ;
      1 1 0 ];
%matriz de paridad transpuesta
PT = transpose(P);
%matriz generadora
G = [ P I];
% U mensajes codificados <mod2>
U = mod(m * G, 2)

% mensajes codificado sin <mod2>
aux = m * G;

%un solo mensaje codificado en <mod2>
U0 = mod(m(8,:)*G,2);


%--------------------------------------------Decodificacion


%matriz verificadora de paridad
H = [ I PT ];
%matriz verificadora de paridad transpuesta
HT = [ I ;
       PT ];
%errores
e = [ 0 0 0 0 0 0 ;
      0 0 0 0 0 1 ;
      0 0 0 0 1 0 ;
      0 0 0 1 0 0 ;
      0 0 1 0 0 0 ;
      0 1 0 0 0 0 ;
      1 0 0 0 0 0 ;
      0 0 0 0 1 1 ]
  

%sindromes
s = mod(e * HT, 2)

%sindromes sin <mod2>
sm = e*HT;

%mensajes por HT
aux = mod(U*HT,2);

%error doble modificando los bits (5,6) palabra original     1 0 0 1 1 1
r = [0 1 0 1 1 1];

%palabra recibida por HT
s = r*HT;

%correcion a la palabra
correcion = mod(r + [1 1 0 0 0 0],2);


