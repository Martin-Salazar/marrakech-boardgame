#include <iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

struct Jugadores
{
	string nombre;
	int monedas;
	int alfombras;
};
struct Hassan
{
	int fila;
	int columna;
	int direccion;
	char subhassan;
};
struct Alfombras
{
	char posicion;
	int principal;
	int segundario1;
	int segundario2;
};
struct Caminos
{
	int fil;
	int col;
};
void menu(Jugadores jugadores[]);
void llenar (char juego[][7]);
void color  (int turno);
void imprimir (char juego[][7], Jugadores jugadores[], string instruccion, int a, Hassan hassan);
int girar (char juego[][7], Hassan hassan, int direccion);
int errores1 (int error, int direccion);
int dado();
Hassan fmover (Hassan hassan, char juego [][7], int mover);
void falfombras (Alfombras alfombras[], Hassan hassan, char juego[][7], int turno, int nalfombras);
void actualizar(Caminos caminos[]);
int buscar (Caminos caminos[],int k, char juego[][7], int fila, int columna, int turno, Hassan hassan, Caminos Caminos2);
int pagar (char juego[][7],Hassan hassan, int turno, Caminos caminos[], Caminos caminos2[]);
int revisar( Caminos caminos2[], int fila, int columna); 
int reint (char numero);

int main() 

{

	char juego[7][7], enter, revisar;
	Jugadores jugadores[2];
	Hassan hassan;
	Caminos caminos[49], caminos2[49];
	int fin=1, turno, direccion, mover, nalfombras=0, pago;
	string instruccion=" ";
	int victoria=8, cont0=0, cont1=0, r, s;
	
	menu(jugadores);
	llenar (juego);
	
	hassan.fila=3;
	hassan.columna=3;
	hassan.direccion=2;
	hassan.subhassan='*';
	
	Alfombras alfombras[30];
	
	while(fin != 0)
	   
	    for (turno=0; turno<2; turno++) 
	    {
	       
	     
	       cout<<"Pague "<<pago<<"     \n";
	       instruccion="A DONDE QUIERE GIRAR A HASSAN? 1=ARI 2=ABA 3=DER 4=IZQ";
	       imprimir (juego, jugadores, instruccion,turno,hassan);
	       cin>>revisar;
	       direccion=reint(revisar);
	       hassan.direccion=girar(juego, hassan, direccion);
	       instruccion="HASSAN GIRADO, PARA LANZAR EL DADO OPRIMA UNA LETRA";
	       imprimir (juego, jugadores, instruccion,turno,hassan);
	       cin>> enter;
	       mover=dado();
	       instruccion="OPRIMA CUALQUIER LETRA PARA MOVER A HASSAN";
	       imprimir (juego, jugadores, instruccion,turno,hassan);
	       cin>>enter;
	       hassan=fmover(hassan, juego, mover);
	       instruccion="PARA VER CUANDO DEBE PAGAR OPRIMA UNA LETRA";
	       imprimir (juego, jugadores, instruccion,turno,hassan);
	       cin>>enter;
	       pago=pagar(juego,hassan,turno,caminos,caminos2);
	       cout<<"Debe pagar "<<pago<<" monedas\n";
	       jugadores[turno].monedas= jugadores[turno].monedas-pago;
	       instruccion="INGRESE LAS COORDENADAS DE LA ALFOMBRA";
	       imprimir (juego, jugadores, instruccion,turno,hassan);
	       falfombras(alfombras, hassan, juego, turno, nalfombras);
	       jugadores[turno].alfombras--;
	      
 
           if(((jugadores[0].monedas==0)||(jugadores[1].monedas==0))&&(turno==1))
                {
                	fin=0;
                	{
					if(jugadores[0].monedas>jugadores[1].monedas)
                	    victoria=0; 
                	else 
                	    victoria=1;
                    }
				}
	       if((jugadores[0].alfombras==0)&&(jugadores[1].alfombras==0))
	            {

	            	fin=0;
					for(r=0; r<7; r++)
	            	   {
	            	   	for(s=0; s<7; s++)
	            	       {
							   if(juego[r][s]=='H')
	            	   		    cont0++;
						
							   if(juego[r][s]=='O')
	            	   	        cont1++;
						    }
						}
						
					if(hassan.subhassan=='H')
						cont0++;
					else 
						if(hassan.subhassan=='O')
							cont1++;

					cout<<jugadores[0].nombre<<" tiene "<<cont0+jugadores[0].monedas<<" puntos "<<jugadores[1].nombre<<" tiene "<<cont1+jugadores[1].monedas<<" puntos ";
					if((jugadores[0].monedas+cont0)>(jugadores[1].monedas+cont1))
					    victoria=0;
                    if((jugadores[0].monedas+cont0)<(jugadores[1].monedas+cont1))
                	    victoria=1;
                    if((jugadores[0].monedas+cont0)==(jugadores[1].monedas+cont1))
                        victoria=3;
				}   
     	}

    
    if(victoria==0)
        {
        	cout<<"\n\n";
    cout<<"                   o     o o .oOOo. ooooo .oOOo.  .oOOo. o       oo \n";    
    cout<<"                   O     O O O    O   O   O    O  O   `O O      O O  \n";    
    cout<<"                   O     O O O        O   O    O oOOooO' O     O  O  \n"; 
    cout<<"                   `O   O' O O        O   O    O  O   `O O   oOoooO \n";
    cout<<"                    `O O'  O O    O   O   O    O  O    O O   O    O  \n";
    cout<<"                     `O'   O `OooO'   O   `OooO'  O    O O  O     O  \n";
    cout<<"\n                        © Urbina Robert & Salazar Martin ©";
    cout<<"\n\n\n\n";
	    cout<<"                                     "<<jugadores[0].nombre;
	    color(0); 
	    }
	if(victoria==1)
        {
        		cout<<"\n\n";
    cout<<"                   o     o o .oOOo. ooooo .oOOo.  .oOOo. o       oo \n";    
    cout<<"                   O     O O O    O   O   O    O  O   `O O      O O  \n";    
    cout<<"                   O     O O O        O   O    O oOOooO' O     O  O  \n"; 
    cout<<"                   `O   O' O O        O   O    O  O   `O O   oOoooO \n";
    cout<<"                    `O O'  O O    O   O   O    O  O    O O   O    O  \n";
    cout<<"                     `O'   O `OooO'   O   `OooO'  O    O O  O     O  \n";
    cout<<"\n                        © Urbina Robert & Salazar Martin ©";
    cout<<"\n\n\n\n";
	    cout<<"                                     "<<jugadores[1].nombre;
        color(1); 
	    }
	if(victoria==3)
	    {
		cout<<"\n\n";
   		cout<<"                    ooooooO  o     o  Oooooo.      oo  ooooo ooooooO \n";    
  		cout<<"                    O        Oo   oO  O      o    O O    O   O       \n";    
  		cout<<"                    OooooO   O`o o'O  O      o   O  O    O   OooooO  \n"; 
   		cout<<"                    O        O `o' O  Oooooo´  oOoooO    O   O       \n";
   		cout<<"                    O        O     O  O        O    O    O   O       \n";
   		cout<<"                    OoooooO  O     O  O       O     O    O   OoooooO \n";
    	cout<<"\n                        © Urbina Robert & Salazar Martin ©";
    	cout<<"\n\n\n\n";
	    cout<<"                                "<<jugadores[0].nombre<<"  &  "<<jugadores[1].nombre;
	    system("color 0F");
	    }
	    
	
	   
}
void menu(Jugadores jugadores[])
 {
 	system("color 0F");
	cout<<"\n";  
 	cout<<"            o     o                           O                    O      \n";    
    cout<<"            Oo   oO                           O                    O        \n";    
    cout<<"            O`o o'O  oOOo. oOOo. oOOo.  oOOo. O  .o  .oOOo. .oOOo. OoOOo.  \n"; 
    cout<<"            O `o' O .ooooO O  `' O  `' .ooooO OoO'   OooooO O    ' O    O \n";
    cout<<"            O     O O    O O     O     O    O O `o.  O.     O    . O    O \n";
    cout<<"            O     O `OooOO O     O     `OooOO O  `o  `Oooo' `OooO' O    O   \n";
                                                                  
 	cout<<"\n                        © Urbina Robert & Salazar Martin ©";
 	cout<<"\n\n                DIGITE EL NOMBRE DEL JUGADOR UNO       ";
 	cin>>jugadores[0].nombre;
    jugadores[0].monedas=30;
    jugadores[0].alfombras=15;
 	cout<<"                                _  ___  ____   \n";
	cout<<"                                L V // (_ (_`  \n";
	cout<<"                                 L_//  __)__)  \n";
 	cout<<"\n                DIGITE EL NOMBRE DEL JUGADOR DOS       ";
 	cin>>jugadores[1].nombre;
    jugadores[1].monedas=30;
    jugadores[1].alfombras=15;
 	cout<<"\n\n";
 	
 }
 void llenar (char juego[][7])
 {
	int i, j;
 	  for (i=0; i<7; i++)
 	    for (j=0; j<7; j++)
 	    juego[i][j]='*'; 
 	  juego[3][3]='v';  
 }
 void color (int turno)
 {
 	if (turno==0)
 	   {system("color 3F");}
 	else
	   {system("color 9F");}   
 }
 int reint (char numero)
 {
 	int con=0;
 	while(con==0)
 	{
	 	 if((numero=='0')||(numero=='1')||(numero=='2')||(numero=='3')||(numero=='4')||(numero=='5')||(numero=='6'))
 	     {
		  return (numero-'0');
		  con=1;
	     }
        else 
 	     {
 	     cout<<"Digite un entero";
 	     cin>>numero;
 	     }
 	     
    }
    
 }
void imprimir (char juego[][7], Jugadores jugadores[], string instruccion, int turno, Hassan hassan)
 {
 	int i, j, f=0, c;
 	color(turno);
 	cout<<"==================================  MARRAKECH ==================================\n";
 	for (i=0; i<2; i++)
    	{
	  	   cout<<jugadores[i].nombre<<"  TIENE    ";
 	       cout<<"MONEDAS ="<<jugadores[i].monedas<<"     ";
 	       cout<<"# ALFOMBRAS ="<<jugadores[i].alfombras;
 	       if(i==1)
 	          cout<<" Signo 'O'\n";
 	       else 
 	          cout<<" Signo 'H'\n";
 	    }

       cout<<"\n ";
      for (c=0; c<7; c++)
         cout<<" "<<c;
       cout<<"\n";
 	  for (i=0; i<7; i++)
 	    {
 	      cout<<f<<" ";
 	      f++;
		 for (j=0; j<7; j++)
		    {
		     
   	        cout<<juego[i][j]<<" ";
   	              	            
   	        }
   	     if(i==3)
   	       cout<<"   "<<instruccion;
   	    cout<<"\n";

 	     
 	    }
 	   
      cout<<"\nHassan esta sobre "<<hassan.subhassan<<" ("<<hassan.fila<<","<<hassan.columna<<")";
      if(turno==0)
 	   cout<<"                                 "<<jugadores[0].nombre<<" Esta jugando \n\n";
 	else 
 	   cout<<"                                 "<<jugadores[1].nombre<<" Esta jugando \n\n";
 }
int girar (char juego[][7], Hassan hassan, int direccion)
 {
 	int a, e=1, error=1; 
 	while(e!=0)
 	{	 
     	switch(direccion)
     	{
 	        case 1: {juego[hassan.fila][hassan.columna]='^'; break;}
 	        case 2: {juego[hassan.fila][hassan.columna]='v'; break;}
 	        case 3: {juego[hassan.fila][hassan.columna]='>'; break;}
 	        case 4: {juego[hassan.fila][hassan.columna]='<'; break;}
			default:break;
        }
    a=hassan.direccion*direccion;
    if((a==2)||(a==12))
      direccion= errores1(error, direccion);
    else 
	  e=0;
    }
    return direccion;
} 
int errores1 (int error, int direccion)
 {
 	char revisar;
    system("color 4F");
	cout<<" No puede hacer giros de 180 grados, elija otra direccion \n";
	cin>>revisar;
    direccion=reint(revisar);
	direccion;
	return direccion; 
 }
 
int dado()
 {
 	int mover;
 	srand(time(0));
 	mover=1+rand()%4;
	cout<< "EL DADO DIO: "<< mover <<" \n";	
	return mover;
 }
Hassan fmover (Hassan hassan, char juego [][7], int mover)
 {
 	
	juego[hassan.fila][hassan.columna]=hassan.subhassan;
 	while(mover!=0)
 	{
 	 switch(hassan.direccion)
    	{
	 
 	    case 1: {  
 	                if(hassan.fila==0)
 	                {
 	                	
 	                	if ((hassan.columna==1)||(hassan.columna==3)||(hassan.columna==5))
 	                	    {
						    hassan.columna--;
						    mover--;
					        hassan.direccion=2;break;
					        }
					    if ((hassan.columna==0)||(hassan.columna==2)||(hassan.columna==4))
					        {
							hassan.columna++;
							mover--;
					        hassan.direccion=2;break;
					        }
					    if(hassan.columna==6)
					        {
					        mover--;
							hassan.direccion=4;break;
						    }
 	                }
 	                else
 	                hassan.fila--;
 	                mover--;
 	             break;
				}
 	              
     	case 2: {  
 	                if(hassan.fila==6)
 	                {
 	                	
 	                	if ((hassan.columna==1)||(hassan.columna==3)||(hassan.columna==5))
 	                	    {
						    hassan.columna++;
						    mover--;
					        hassan.direccion=1;break;
					        }
					    if ((hassan.columna==2)||(hassan.columna==4)||(hassan.columna==6))
					        {
							hassan.columna--;
							mover--;
					        hassan.direccion=1;break;
					        }
					    if(hassan.columna==0)
					        {
					        mover--;
							hassan.direccion=3;break;
						    }
 	                }
 	                else
 	                hassan.fila++;
 	                mover--;
 	             break;
				}
        case 3: {
        	        
 	                if(hassan.columna==6)
 	                {
 	                	
 	                	if ((hassan.fila==2)||(hassan.fila==4)||(hassan.fila==6))
 	                	    {
						    hassan.fila--;
						    mover--;
					        hassan.direccion=4;break;
					        }
					    if ((hassan.fila==1)||(hassan.fila==3)||(hassan.fila==5))
					        {
							hassan.fila++;
							mover--;
					        hassan.direccion=4;break;
					        }
					    if(hassan.fila==0)
					        {
					         mover--;
							 hassan.direccion=2;break;
						    }
 	                }
 	                else
 	                hassan.columna++;
 	                mover--;
 	             break;
	            }
	    case 4: {
 	                if(hassan.columna==0)
 	                {
 	                	
 	                	if ((hassan.fila==0)||(hassan.fila==2)||(hassan.fila==4))
 	                	    {
						    hassan.fila++;
						    mover--;
					        hassan.direccion=3;break;
					        }
					    if ((hassan.fila==1)||(hassan.fila==3)||(hassan.fila==5))
					        {
							hassan.fila--;
							mover--;
					        hassan.direccion=3;break;
					        }
					    if(hassan.fila==6)
					        {
					         mover--;
					         hassan.direccion=1;break;
						    }
 	                }
 	                else
 	                hassan.columna--;
 	                mover--;
 	             break;
	            }
	    default: break;
        }
	}
	hassan.subhassan=juego[hassan.fila][hassan.columna];
	switch(hassan.direccion)
     	{
 	        case 1: {juego[hassan.fila][hassan.columna]='^'; break;}
 	        case 2: {juego[hassan.fila][hassan.columna]='v'; break;}
 	        case 3: {juego[hassan.fila][hassan.columna]='>'; break;}
 	        case 4: {juego[hassan.fila][hassan.columna]='<'; break;}
			default:break;
        }
    return hassan;
 }
 
void falfombras (Alfombras alfombras[],  Hassan hassan, char juego [][7], int turno, int nalfombras)
 {
 	int q=0, prin, w=0, seg1, e=0, errore=9, seg2, r=0, t, errory, y, g=0;
 	char pos, revisar;
	char u; 
 	while(g==0)
    {
      q=0; w=0; e=0; r=0; 
	  while (q==0)
	   {
	  	  cout<<"Ingrese si la alfombra va estar sobre una fila (f) o columna (c)";
		  cin>>pos;
	  	  if((pos=='c')||(pos=='f'))
	      {
	  	      	q=1;
	  	      	color(turno);
	      }
	       else 
	      {
	         system("color 4F");
			 cout<<"No ingreso un caracter correcto, intente nuevamente \n";
	      }
	      
      }
     while (w==0)
       {
          cout<<"Ingrese en que columna/fila pondra la alfombra";
          cin>>revisar;
	      prin=reint(revisar);
		  if(pos=='c')
            {
			if(((prin==hassan.columna+1)||(prin==hassan.columna-1)||(prin==hassan.columna))&&(prin!=-1)&&(prin!=7))
                {
				  w=1;
				  if(prin==hassan.columna)
				   {
				     if(hassan.fila<2)
				        {errore=hassan.fila-1;}
				     if(hassan.fila>4)
				        {errore=hassan.fila+1;}
			       }
				}
            }
		  else 
		    {
		  	if(((prin==hassan.fila+1)||(prin==hassan.fila-1)||(prin==hassan.fila))&&(prin!=-1)&&(prin!=7))
	   	  	      {
				    w=1;
				    if(prin==hassan.fila)
				    {
				     if(hassan.columna<2)
				        {errore=hassan.columna-1;}
				     if(hassan.columna>4)
				        {errore=hassan.columna+1;}
				    }
			      }
		    }
		  if (w==0)
		   {
            system("color 4F");
			cout<<"La  alfombra debe estar al lado de la posicion de hassan y dentro del tablero \n";
	       }
	       else 
	        color(turno);
		  	
	   } 
	 while (e==0)
	  {
	  	cout<<"Ingrese la parte de la alfombra que es adyacente a hassan";
	  	cin>>revisar;
	    seg1=reint(revisar);
	  	if(pos=='c')
	  	{
	  	    if (((prin==hassan.columna-1)||(prin==hassan.columna+1))&&(seg1!=-1)&&(seg1!=7))
	  	    {
	  	        if (seg1==hassan.fila)
	  	           e=1;
			}
		    if (prin==hassan.columna)
		    {
		    	if (((seg1==hassan.fila-1)||(seg1==hassan.fila+1))&&(seg1!=errore)&&(seg1!=-1)&&(seg1!=7))
		    	   e=1;
			}
	    }
		else
	    {
		    if (((prin==hassan.fila-1)||(prin==hassan.fila+1))&&(seg1!=-1)&&(seg1!=7))
	  	    {
	  	        if (seg1==hassan.columna)
	  	           e=1;
			}
		    if (prin==hassan.fila)
		    {
		    	if (((seg1==hassan.columna-1)||(seg1==hassan.columna+1))&&(seg1!=errore)&&(seg1!=-1)&&(seg1!=7))
		    	   e=1;
	     	}
	    }
	    if(e==0)
	    {
	    	system("color 4F");
		    cout<<"La  alfombra debe estar al lado de la posicion de hassan y dentro del tablero \n";
		}     
	    else
		    color(turno);
	  }  
	 while (r==0)
	  { 
	    cout<<"Ingrese la segunda parte de la alfombra";
	    cin>>revisar;
	    seg2=reint(revisar);
	  	if(((seg2==seg1+1)||(seg2==seg1-1))&&(seg2!=-1)&&(seg2!=7))
	  	    if(pos=='c')
	  	      {
				if (seg2!=hassan.fila)
	  	        {
				    r=1;
	  	     	    color(turno);
	  	        }
	  	       else 
	  	            r=0;
	  	       }
	  	    else 
	  	      {
				if (seg2!=hassan.columna)
	  	        {
	  	            r=1;
	  	         	color(turno);
		        }
		        else 
		            r=0;
		       }
		if(r==0)
		    {
			  system("color 4F");
			  cout<<"La  alfombra debe estar unida formando un rectangulo, dentro del tablero y no debajo de hassan \n";
		    }
	  }
	  if (turno==0)
	   	   {y=1;}
	   	  else
	   	   {y=0;}
	 for(t=0; t<60; t++)
	   {
	   	  if((alfombras[t].posicion==pos)&&(alfombras[t].principal==prin)&&
			 (((alfombras[t].segundario1==seg1)&&(alfombras[t].segundario2==seg2))||
			 ((alfombras[t].segundario1==seg2)&&(alfombras[t].segundario2==seg1))))
	        {
			    if(((pos=='c')&&(juego[seg1][prin]==juego[seg2][prin]))||((pos=='f')&&(juego[prin][seg1]==juego[prin][seg2])))		    
		         	{
		         	errory=1;
		    	    t=61; 
		     	    }
		     	else 
		     	    {
		     	    errory=0;
					}
		    }
		  else 
		    {
			errory=0;
			}
	   }
     if(errory==1)
	   {
	    system("color 4F"); 
		cout<<"Esta alfombra ya fue ingresada ingrese otra posicion de alfombra\n";
	   }
     else 
       g=1;
   }
   
      alfombras[nalfombras].posicion=pos;
	  alfombras[nalfombras].principal=prin;
	  alfombras[nalfombras].segundario1=seg1;
	  alfombras[nalfombras].segundario2=seg2;
	  nalfombras++;
	  if(turno==0)
        u='H';
      else
        u='O';
      if(pos=='c')
	    {
	    juego[seg1][prin]=u;
		juego[seg2][prin]=u;
		}   
	  else 
	    {
	    juego[prin][seg1]=u;
	    juego[prin][seg2]=u;
	    }
 }
 
 void actualizar (Caminos caminos[])
 {
 	int i;
 	for(i=0; i<49; i++)
 	   {
		caminos[i].fil=caminos[i+1].fil;
	    caminos[i].col=caminos[i+1].col;
        }
 }
 int revisar( Caminos caminos2[], int fila, int columna)
 { 
 	int i;
 	for(i=0; i<49; i++)
		    {
		   	if((fila==caminos2[i].fil)&&(columna==caminos2[i].col))
				  return 1;
			}
		 return 0;
 }
int buscar (Caminos caminos[], int k, char juego[][7], int fila, int columna, int turno, Hassan hassan, Caminos caminos2[])
 {
 	int re;
	if (turno==0)
 	    {
		    {if((juego[fila+1][columna]==hassan.subhassan)&&(fila+1!=7))
 	            {
			        re=revisar(caminos2, fila+1, columna);
			        if(re==0)
				 	   {
						k++;
				        caminos[k].fil=fila+1;
 	                    caminos[k].col=columna;
 	                   }
		    	}
         	}
 	        {if((juego[fila-1][columna]==hassan.subhassan)&&(fila-1!=-1))
 	            {
				    re=revisar(caminos2, fila-1, columna);
			        if(re==0)
				 	   {
						k++;
				        caminos[k].fil=fila-1;
 	                    caminos[k].col=columna;
 	                   }
				}
	     	}
 	        {if((juego[fila][columna+1]==hassan.subhassan)&&(columna+1!=7))
 	            {
 	                re=revisar(caminos2, fila, columna+1);
			        if(re==0)
				 	    {   
						 k++;
			        	caminos[k].fil=fila;
 	                    caminos[k].col=columna+1;
 	                    }
				}
		    }
 	        {if((juego[fila][columna-1]==hassan.subhassan)&&(columna-1!=-1))
 	            {
 	                re=revisar(caminos2, fila, columna-1);
			        if(re==0)
				 	    {   
						 k++;
				        caminos[k].fil=fila;
 	                    caminos[k].col=columna-1;
 	                    }
			    }
		    }
       	}
    else 
        {
		    {if((juego[fila+1][columna]==hassan.subhassan)&&(fila+1!=7))
 	            {
 	                re=revisar(caminos2, fila+1, columna);
			        if(re==0)
				 	   { 
						k++;
				        caminos[k].fil=fila+1;
 	                    caminos[k].col=columna;
 	                   }
			    }
		    }
 	        {if((juego[fila-1][columna]==hassan.subhassan)&&(fila-1!=-1))
 	            {
				    re=revisar(caminos2, fila-1, columna);
			        if(re==0)
				 	   {
					    k++;
				        caminos[k].fil=fila-1;
 	                    caminos[k].col=columna;
 	                   }
                }
		    }
 	        {if((juego[fila][columna+1]==hassan.subhassan)&&(columna+1!=7))
 	            { 
				    re=revisar(caminos2, fila, columna+1);
			        if(re==0)
				 	   {  
						k++;
			         	caminos[k].fil=fila;
 	                    caminos[k].col=columna+1;
 	                   }
				}
		    }
 	        {if((juego[fila][columna-1]==hassan.subhassan)&&(columna-1!=-1))
 	            {
 	                re=revisar(caminos2, fila, columna-1);
			        if(re==0)
				 	   {   
						 k++;
			        	caminos[k].fil=fila;
 	                    caminos[k].col=columna-1;
 	                    }
				}
	     	}
       	}
        
    return k;
 }
 int pagar (char juego[][7],Hassan hassan, int turno, Caminos caminos[], Caminos caminos2[])
 {
    int i, k=0, g=0, cont=0, ya=0;
    for(i=0; i<49; i++)
	   {
	     caminos[i].fil=-1;
	     caminos[i].col=-1;
	   }
	for(i=0; i<49; i++)
	   {
	     caminos2[i].fil=-1;
	     caminos2[i].col=-1;
	   }
    caminos[0].fil=hassan.fila;
    caminos[0].col=hassan.columna;
   
 	while(caminos[0].fil!=-1)
 	    {
			ya=revisar(caminos2, caminos[0].fil, caminos[0].col);
			    
			if(cont==0)
			   {
			   {if((turno==0)&&(hassan.subhassan=='O')&&(ya==0))
 	             cont++;}
 	           {if((turno==1)&&(hassan.subhassan=='H')&&(ya==0))
 	             cont++;}
 	           }
 	        else
 	           {
 	           {if((turno==0)&&((juego[caminos[0].fil][caminos[0].col])=='O')&&(ya==0))
 	             cont++;}
			   {if((turno==1)&&((juego[caminos[0].fil][caminos[0].col])=='H')&&(ya==0))
 	             cont++;}
 	           }
 	         
	        caminos2[g].fil=caminos[0].fil;
	        caminos2[g].col=caminos[0].col;
	        g++;

 	        if(cont!=0)
 	            {
				k=buscar(caminos, k, juego, caminos[0].fil, caminos[0].col, turno, hassan, caminos2);
 	            k--;
 	            }
 	        
 	        actualizar(caminos);
 	        
		}
    
    return cont;
 }
 
 
 
 
 
	
	

