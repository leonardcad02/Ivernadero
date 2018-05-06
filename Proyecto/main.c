#include "D:\Proyecto\main.h"

#fuses  HS,NOWDT,NOPROTECT,NOLVP
#include <rtcc.c>
#include <HDM64GS122.C>
#include <GRAPHICS.C>
#include <portada.h>
#include <finalizado.h>
#include <1wire.c> //sensor ds1820
#include <ds1820.c>


int s,dayset,monthset,yrset,hrset,minset,hr,min,sec,oldsec,dia,mes,dow,yr,bandera =0,tempminima = 18,tempset,tempmaxima = 28,tempset2,repos = 10,reposset,rieg = 10,riegset,num = 5,numset,dias=1,diasset;
int lun=0,mar=0,mie=0,jue=0,vie=0,sab,dom= 0;
unsigned int1 am_pm;
float temp=0;
char time[];
char tim[];
char tim2[];
char Pgeneral[20];
char Pgeneral6[20];
char Pgeneral2[20];
char Pgeneral3[20];
char Pgeneral4[20];
char Pgeneral5[20];

char MENSAJE1[]="SISTEMA INVERNADERO";
char SETTIME[]="Configurar Sistema?";
char TIMENOW[]="Hora/Fecha Actual:";
char HORA[] = "Conf Hora & Fecha";
char TEMPERATURA[] = "Conf Temperatura";
char RIEGO[] = "Conf Riego";
char DOMINGO[]=   "Domingo";
char LUNES[]=       "Lunes";
char LU[]="Lu";
char MA[]="Ma";
char MI[]="Mi";
char JU[]="Ju";
char VI[]="Vi";
char SA[]="Sa";
char D[]="Do";
char MARTES[]=     "Martes";
char MIERCOLES[]= "Miercoles";
char JUEVES[]=      "Jueves";
char VIERNES[]=     "Viernes";
char SABADO[]=     "Sabado";
char MIERCO[]= "Mierco";
char VIERNE[]=     "Vierne";
char DOMING[]=   "Doming";
char SI[]="Si";
char NOO[]="No";
char SET_TIME[]="Hora";
char SETDATE[]="Fecha";
char SALIR[]="Salir";
char AJUSTEHORA[]="AJUSTE DE HORA";
char AJUSTEFECHA[]="AJUSTE DE FECHA";
char ESTABLECER[]="Establecer";
char AM[]="AM";
char PM[]="PM";
char h[]="h";
char m[]="m";
char DATOS[]="Datos";
char DATOS2[]="Guardados!";
char TEMPACTUAL[]= "TEMP ACTUAL";
char MINI[]="Min";
char MAX[] ="Max";
char TEMP_MIN[]="Temp Minima";
char TEMP_MAX[]="Temp Maxima";
char NEBULIZACION[] = "Nebulizacion";
char GOTEO[]="Goteo";
char CON_RIEGO[]="Configurar Riego";
char SENSADO[]="Sensado";
char TEMPORIZADO[]="Temporizado";
char TIEMPO_REPOSO[] ="Tiempo de Reposo";
char TIEMPO_RIEGO[] = "Tiempo de Riego";
char NUM_CICLOS[] = "Numero de Ciclos";
char CICLOS[]="Ciclos";
char DIAS_TRABAJO[] = "Dias de Trabajo"; 

#define NIVEL  INPUT(PIN_B2)


void leerRTC(){
    ds1307_get_time(hr,am_pm,min,sec);
    ds1307_get_date(dia,mes,yr,dow);
    
    if(am_pm==1)
    time='P';
    else
    time='A';
    delay_us(100);
}


void main()
{

   setup_adc_ports(AN0|VSS_VDD);
   setup_adc(ADC_CLOCK_DIV_2|ADC_TAD_MUL_0);
   setup_psp(PSP_DISABLED);
   setup_wdt(WDT_OFF);
   setup_timer_0(RTCC_INTERNAL);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_timer_3(T3_DISABLED|T3_DIV_BY_1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   setup_oscillator(OSC_8MHZ|OSC_TIMER1|OSC_31250|OSC_PLL_OFF);

   // TODO: USER CODE!!
   
   int8 xa=24,ya=32;


   glcd_init(ON);       // Inicialización de GLCD
   glcd_fillScreen(0); //LIMPIAMOS LA PANTALLA 
   glcd_portada();
   delay_ms(1000);
  
INICIO:
   glcd_fillScreen(0); //==============

  // ds1307_init();
   glcd_rect(0,0,127,63,NO,ON);
   glcd_rect(1,1,126,62,NO,ON);
   glcd_text57(5,5,MENSAJE1, 1, 1);
   glcd_text57(8,20,SETTIME, 1, 1);
   glcd_rect(5,37,61,58,YES,ON);
   glcd_rect(65,37,120,58,YES,ON);
   glcd_text57(28,44,SI, 1, 0);
   glcd_text57(86,44,NOO, 1, 0);
   
   glcd_rect(6,38,60,57,NO,OFF);//dibuja selector
      
   set_adc_channel(0); // lectura del teclado puerto analogo 
   delay_us(20);
   

   
   START1:
   
   s = read_adc();
   delay_ms(100); //***************************
   
   while(s > 240){
    s = read_adc();
    delay_ms(50);
   }
   if(s > 195 && s < 225) //enter
       goto MENU; //entra a la configuracion de hora/temperatura/riego 
      
   else if (s > 165 &&  s < 185){  // pulsa la tecla derecha 
      
       glcd_rect(6,38,60,57,NO,ON);
       glcd_rect(66,38,119,57,NO,OFF);
       delay_ms(100);
       s = read_adc();
       delay_us(40);
          while(s > 240){  // ha espera del nuevo enter 
            s = read_adc();
            delay_ms(50);//*************************
            }
               if(s > 195 && s < 225)
           goto SISTEMA; //enter cuando no se elige configurar el sistema 
    if(s > 115 && s < 135){// pulsa la tecla izquierda
           glcd_rect(66,38,119,57,NO,ON);
           glcd_rect(6,38,60,57,NO,OFF);
           delay_ms(50);
           goto START1;
       }   
       else 
           goto START1;
   }goto START1;
  

   

   
  MENU:
   glcd_fillScreen(0);
   glcd_rect(0,0,127,63,NO,ON);
   glcd_rect(1,1,126,62,NO,ON);
   glcd_rect(5,5,122,22,YES,ON);
   glcd_text57(10,10,HORA, 1, 0);
   glcd_rect(5,25,122,39,YES,ON);
   glcd_text57(10,30,TEMPERATURA, 1, 0);
   glcd_rect(5,42,122,56,YES,ON);
   glcd_text57(10,47,RIEGO, 1, 0);
   
   glcd_rect(6,6,121,21,NO,OFF); // rectangulo selector 
 
 CUADRO_MENU:
 
    s = read_adc();
    delay_ms(100); //***************************
   
   while(s > 240){
    s = read_adc();
    delay_ms(50);
   }
    if(s > 195 && s < 225) //enter
       goto CONF_RTC;
    else if(s > 60 && s < 90){  // pulsa tecla abajo
          
           glcd_rect(6,6,121,21,NO,ON); //apga el recuadro de la casilla anterior
           glcd_rect(6,26,121,38,NO,OFF);//enciende el proximo recuadro 
           delay_ms(100);
           s = read_adc();
           delay_us(40);
          
          while(s > 240){  // ha espera del nuevo enter 
            s = read_adc();
            delay_ms(50);//*************************
          }
    
    }
    if((s > 195 && s < 225))
           goto CONF_TEMP; 

     else   if(s > 60 && s < 90){ // presiona tecla abajo
               goto segunda_abajo;      

        }
     else  goto  CUADRO_MENU;     
   
          
    
  segunda_abajo:
  
          
           glcd_rect(6,26,121,38,NO,ON);
           glcd_rect(6,43,121,55,NO,OFF);
           delay_ms(50);
           s = read_adc();
           delay_us(40);
        
       while(s > 240){  // ha espera del nuevo enter 
            s = read_adc();
            delay_ms(50);//*************************
            }
       if((s > 195 && s < 225)){
           goto CONF_RIEGO; }
           
       if( s > 10 && s < 40){
           glcd_rect(6,43,121,55,NO,ON);
           glcd_rect(6,26,121,38,NO,OFF);
           delay_ms(50);
           s = read_adc();
           delay_us(40);
        
        while(s > 240){  // ha espera del nuevo enter
            s = read_adc();
            delay_ms(50);//*************************
            }
       if((s > 195 && s < 225)){
           goto CONF_TEMP; }
           
       if( s > 10 && s < 40){
          glcd_rect(6,26,121,38,NO,ON);
          glcd_rect(6,6,121,21,NO,OFF);
           delay_ms(50);
       
              
          goto  CUADRO_MENU;
        
        
        }
       }
           
           goto segunda_abajo;
            
  CONF_RTC: 
  
  glcd_fillScreen(0);
  glcd_rect(0,0,127,63,NO,ON);
  glcd_rect(1,1,126,62,NO,ON);
  glcd_text57(5,5,TIMENOW, 1, 1);
  leerRTC();
  sprintf(Pgeneral,"\%02d:\%02d:\%02d \%cM", hr,min,sec,time);
  glcd_text57(5,15,Pgeneral, 1, 1);
  sprintf(Pgeneral,"\%02d/\%02d/\%02d", dia,mes,yr);
  glcd_text57(5,25,Pgeneral, 1, 1);
  
    if(dow == 1)
      glcd_text57(60,25,DOMINGO, 1, 1);
    if(dow == 2)
      glcd_text57(60,25,LUNES, 1, 1);
    if(dow == 3)
      glcd_text57(60,25,MARTES, 1, 1);
    if(dow == 4)
      glcd_text57(60,25,MIERCOLES, 1, 1);
    if(dow == 5)
      glcd_text57(60,25,JUEVES, 1, 1);
    if(dow == 6)
      glcd_text57(60,25,VIERNES, 1, 1);
    if(dow == 7)
      glcd_text57(60,25,SABADO, 1, 1);
  
   glcd_rect(8,37,43,58,YES,ON);
   glcd_rect(46,37,81,58,YES,ON);
   glcd_rect(84,37,119,58,YES,ON);
   
   glcd_rect(9,38,42,57,NO,OFF);

   glcd_text57(14,45,SET_TIME, 1, 0);  
   glcd_text57(49,45,SETDATE, 1, 0); 
   glcd_text57(86,45,SALIR,1,0);
   
   
 START2:
 s= read_adc();
 delay_ms(50);
 
 while(s>230){     //visualizar lectura de RTC
 leerRTC();
 delay_ms(50);
      if (sec != oldsec){
         glcd_text57(5,15,Pgeneral,1,0);
         sprintf(Pgeneral,"\%02d:\%02d:\%02d \%cM",hr,min,sec,time);
         glcd_text57(5,15,Pgeneral,1,1);
         oldsec=sec;
      }
 s =read_adc();
 delay_us(40);
 }
 
   if(s > 195 && s < 225) //enter
       goto CONF_HORA;
   else if (s > 165 &&  s < 185){
       Return1:
       glcd_rect(9,38,42,57,NO,ON);
       glcd_rect(47,38,80,57,NO,OFF);
       glcd_rect(85,38,118,57,NO,ON);
       delay_ms(500);
       s = read_adc();
       delay_ms(50);
       while(s > 240){
            s = read_adc();
            delay_ms(50);//********************
            }
       if(s > 195 && s < 225) //enter
           goto CONF_FECHA;
       if(s > 115 && s < 135){ //devolver
           
           glcd_rect(9,38,42,57,NO,OFF);
           glcd_rect(47,38,80,57,NO,ON);
           glcd_rect(85,38,118,57,NO,ON);
           delay_ms(50);
           goto START2;
       }   
       else if(s > 165 &&  s < 185){ //avanzar
           glcd_rect(9,38,42,57,NO,ON);
           glcd_rect(47,38,80,57,NO,ON);
           glcd_rect(85,38,118,57,NO,OFF);
           delay_ms(100);
           s = read_adc();
           delay_us(40);
           while(s > 240){
           s = read_adc();
           delay_ms(50);//********************
            }
             if(s > 195 && s < 225) //enter
           goto INICIO;
           else if(s > 115 && s < 135)
               goto Return1;
           else if(s > 165 &&  s < 185)
               goto START2;
           else 
               goto START2;    
       }    
   }
    goto START2; 
    
   
   
     CONF_HORA:
    
         glcd_fillScreen(0);
         glcd_rect(0,0,127,63,NO,ON);
         glcd_rect(1,1,126,62,NO,ON);
         glcd_text57(22,5,AJUSTEHORA, 1, 1);
         sprintf(Pgeneral,"\%02d:\%02d \%cM", hr,min,time);
         glcd_text57(20,18,Pgeneral, 2, 1);//aumenta el tamaño del texto de la funcion 
         
         glcd_rect(20,34,40,35,YES,ON);         //   linea que selecciona LA HORA
         glcd_rect(8,40,119,58,YES,ON);         //      recuadro
         glcd_text57(34,46,ESTABLECER, 1, 0);   //
         
         hrset = hr;
         minset = min;
         dayset= dia;
         monthset = mes;
         yrset = yr;
         
     START4:
         glcd_rect(20,34,40,35,YES,ON);
         glcd_rect(52,34,73,35,YES,OFF); 
         glcd_rect(85,34,107,35,YES,OFF);
      
         glcd_rect(9,41,118,57,NO,ON);
             s = read_adc();    
             delay_ms(50);
   
   
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
             }
             if (s > 10 && s < 40){ // tecla arriba cuadrar hora
                 
                 if(hrset > 11)
                     hrset = 0;
                 hrset ++;
                 
                 glcd_rect(20,18,40,32,YES,OFF);
                 sprintf(Pgeneral,"%02d", hrset);
                 glcd_text57(20,18,Pgeneral, 2, 1);
                 delay_ms(100);
                 goto START4;
             }
               else if(s > 60 && s < 90){
                 
                 if(hrset < 1 )
                     hrset = 13;
                 hrset --;
                 glcd_rect(20,18,40,32,YES,OFF);
                 sprintf(Pgeneral,"%02d", hrset);
                 glcd_text57(20,18,Pgeneral, 2, 1);
                 delay_ms(100);
                 goto START4;
             }
         else if(s > 165 &&  s < 185){
                 
     
          START5: 
          
             glcd_rect(20,34,40,35,YES,OFF);
             glcd_rect(52,34,73,35,YES,ON);
             glcd_rect(85,34,107,35,YES,OFF);
             glcd_rect(9,41,118,57,NO,ON);
             delay_ms(200);
             s = read_adc();    
             delay_ms(50);
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
                   }
             if (s > 10 && s < 40){
                 minset ++;
                 if(minset > 59)
                     minset = 0;
                       
                 glcd_rect(52,18,74,32,YES,OFF);
                 sprintf(Pgeneral,"%02d", minset);
                 glcd_text57(52,18,Pgeneral, 2, 1);
                 delay_ms(200);
                 goto START5;
             }
              if(s > 60 && s < 90){
                 
                 minset --;
                 if(minset == -1 )
                     minset = 59;
                 glcd_rect(52,18,74,32,YES,OFF);
                 sprintf(Pgeneral,"%02d", minset);
                 glcd_text57(52,18,Pgeneral, 2, 1);
                 delay_ms(100);
                 goto START5;
             } 
              if (s > 115 && s < 135){
                 
                 glcd_rect(20,34,40,35,YES,ON);
                 glcd_rect(52,34,73,35,YES,OFF);
                 glcd_rect(85,34,107,35,YES,OFF);
                 glcd_rect(9,41,118,57,NO,ON);
                 delay_ms(200);
                 goto START4;
             }
              if(s > 165 &&  s < 185){
                 START6:
                 
                 glcd_rect(20,34,40,35,YES,OFF);
                 glcd_rect(52,34,73,35,YES,OFF); 
                 glcd_rect(85,34,107,35,YES,ON);
                 glcd_rect(9,41,118,57,NO,ON);
                 
                 delay_ms(200);
                 s = read_adc();    
                 delay_ms(50);
                 while(s>230){
                   s = read_adc();    
                   delay_ms(50);
                   }
                  if (s > 10 && s < 40){
                     
                     time = 1;
                     glcd_rect(85,18,102,32,YES,OFF);
                     glcd_text57(86,18,AM, 2, 1);
                     goto START6;
                  }
                   if (s > 60 && s < 90){
                     
                     time = 0;
                     glcd_rect(85,18,102,32,YES,OFF);
                     glcd_text57(86,18,PM, 2, 1);
                     goto START6;
                  }
                  if (s > 115 && s < 135)
                    goto START5;
                 
                 if(s > 165 &&  s < 185){
                    glcd_rect(85,34,107,35,YES,OFF); 
                    glcd_rect(9,41,118,57,NO,OFF);
                    START7:
                    delay_ms(200);
                    s = read_adc();    
                    delay_ms(50);
                    while(s>230){
                       s = read_adc();    
                       delay_ms(50);
                    }
                    if(s > 195 && s < 225)
                        goto SET_RTC;
                    if(s > 115 && s < 135)
                        goto START6;
                 }
                 else
                     goto START7;
             }  
          }
             else 
                 goto START4;
             goto START4;
             
 ////////////////////////////////////////---------------------------------------------------------------------"""""""""""""""""""""""""""""""""""""""
        
         CONF_FECHA:
    
         glcd_fillScreen(0);
         glcd_rect(0,0,127,63,NO,ON);
         glcd_rect(1,1,126,62,NO,ON);
         glcd_text57(22,5,AJUSTEFECHA, 1, 1);
         //year = yr+2000;
         sprintf(Pgeneral,"\%02d/\%02d/\%02d", dia,mes,yr);
         glcd_text57(20,18,Pgeneral, 2, 1);
         
         glcd_rect(20,34,40,35,YES,ON);
         glcd_rect(8,40,119,58,YES,ON);
         glcd_text57(34,46,ESTABLECER, 1, 0);
         
         hrset = hr;
         minset = min;
         dayset = dia;
         monthset = mes;
         yrset = yr;
         START8:
         glcd_rect(20,34,40,35,YES,ON);
         glcd_rect(52,34,73,35,YES,OFF); 
         glcd_rect(85,34,107,35,YES,OFF);
         
         glcd_rect(9,41,118,57,NO,ON);
             s = read_adc();    
             delay_ms(50);
  
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
             }
             if (s > 10 && s < 40){
                 
                 if(dayset > 30)
                     dayset = 0;
                 dayset ++;
                 glcd_rect(20,18,40,32,YES,OFF);
                 sprintf(Pgeneral,"%02d", dayset);
                 glcd_text57(20,18,Pgeneral, 2, 1);
                 delay_ms(100);
                 goto START8;
             }
             else if(s > 60 && s < 90){
                 dayset --;
                 if(dayset < 1 )
                     dayset = 31;
                 
                 glcd_rect(20,18,40,32,YES,OFF);
                 sprintf(Pgeneral,"%02d", dayset);
                 glcd_text57(20,18,Pgeneral, 2, 1);
                 delay_ms(100);
                 goto START8;
             }
             
             else if(s > 165 &&  s < 185){
                 
             START9: 
             glcd_rect(20,34,40,35,YES,OFF);
             glcd_rect(52,34,73,35,YES,ON);
             glcd_rect(85,34,107,35,YES,OFF);
             glcd_rect(9,41,118,57,NO,ON);
             delay_ms(200);
             s = read_adc();    
             delay_ms(50);
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
                   }
             if (s > 10 && s < 40){
                 monthset ++;
                 if(monthset > 12)
                     monthset = 1;
                 
                 glcd_rect(52,18,74,32,YES,OFF);
                 sprintf(Pgeneral,"%02d", monthset);
                 glcd_text57(52,18,Pgeneral, 2, 1);
                 delay_ms(200);
                 goto START9;
             }
              if(s > 60 && s < 90){
                 
                 monthset --;
                 if(monthset == 0 )
                     monthset = 12;
                 glcd_rect(52,18,74,32,YES,OFF);
                 sprintf(Pgeneral,"%02d", monthset);
                 glcd_text57(52,18,Pgeneral, 2, 1);
                 delay_ms(100);
                 goto START9;
             } 
              if (s > 115 && s < 135){
                 
                 glcd_rect(20,34,40,35,YES,ON);
                 glcd_rect(52,34,73,35,YES,OFF);
                 glcd_rect(85,34,107,35,YES,OFF);
                 glcd_rect(9,41,118,57,NO,ON);
                 delay_ms(200);
                 goto START8;
             }
              if(s > 165 &&  s < 185){
                 START10:
                 
                 glcd_rect(20,34,40,35,YES,OFF);
                 glcd_rect(52,34,73,35,YES,OFF); 
                 glcd_rect(85,34,107,35,YES,ON);
                 glcd_rect(9,41,118,57,NO,ON);
                 
                 delay_ms(200);
                 s = read_adc();    
                 delay_ms(50);
                 while(s>230){
                   s = read_adc();    
                   delay_ms(50);
                   }
                  if (s > 10 && s < 40){
                      yrset++;
                      if(yrset > 80)
                          yrset = 2;
                      glcd_rect(85,18,107,32,YES,OFF);
                      sprintf(Pgeneral,"%02d", yrset);
                      glcd_text57(87,18,Pgeneral, 2, 1);
                     goto START10;
                  }
                 
                   if (s > 60 && s < 90){
                     yrset--;
                      if(yrset < 2)
                          yrset = 80;
                      glcd_rect(85,18,107,32,YES,OFF);
                      sprintf(Pgeneral,"%02d", yrset);
                      glcd_text57(87,18,Pgeneral, 2, 1);
                     goto START10;
                  }
                  if (s > 115 && s < 135)
                    goto START9;
                 
                 if(s > 165 &&  s < 185){
                    glcd_rect(85,34,107,35,YES,OFF); 
                    glcd_rect(9,41,118,57,NO,OFF);
                    START11:
                    delay_ms(200);
                    s = read_adc();    
                    delay_ms(50);
                    while(s>230){
                       s = read_adc();    
                       delay_ms(50);
                    }
                    if(s > 195 && s < 225)
                        goto SET_RTC;
                    if(s > 115 && s < 135)
                        goto START10;
                 }
                 else
                     goto START11;
             }  
          }
             else 
                 goto START8;
             goto START8;
             
//////////////////////////////////////--------------------------------------------------------------------""""""""""""""""""""""""""""""""""""""
     
     SET_RTC:
        ds1307_set_date_time(dayset,monthset,yrset,dow,hrset,time,minset,0);
        glcd_fillScreen(0);
        glcd_text57(22,3,AJUSTEFECHA, 1, 1);
        glcd_finalizado();
        glcd_text57(45,25,DATOS, 1, 1);
        glcd_text57(45,35,DATOS2, 1, 1);
        delay_ms(3000);
       
        goto CONF_RTC;

  CONF_TEMP:
        //temp= 36.0;
        temp = ds1820_read();  //funcion
        temp = temp/8;
  
       glcd_fillScreen(0);
       glcd_rect(0,0,127,63,NO,ON);
       glcd_rect(1,1,126,62,NO,ON);
       glcd_text57(22,5,TEMPACTUAL, 1, 1);
       sprintf(Pgeneral6,"%.1f °C",temp);
       glcd_text57(20,18,Pgeneral6, 2, 1);
       
      glcd_rect(8,37,43,58,YES,ON);
      glcd_rect(46,37,81,58,YES,ON);
      glcd_rect(84,37,119,58,YES,ON);
   
      glcd_rect(9,38,42,57,NO,OFF);

      glcd_text57(14,45,MINI, 1, 0);  
      glcd_text57(49,45,MAX, 1, 0); 
      glcd_text57(86,45,SALIR,1,0);
   

    TEMP1:
    
      s = read_adc();
   delay_ms(100); //***************************
   
   while(s > 240){
    s = read_adc();
    delay_ms(50);
   }
   if(s > 195 && s < 225) //enter
       goto CONF_MINI; //entra a la configuracion de hora/temperatura/riego
      
   else if (s > 165 &&  s < 185){  // pulsa la tecla derecha 
       Returno:
       glcd_rect(9,38,42,57,NO,ON);
       glcd_rect(47,38,80,57,NO,OFF);
       glcd_rect(85,38,118,57,NO,ON);
  
       delay_ms(100);
       s = read_adc();
       delay_us(40);
          while(s > 240){  // ha espera del nuevo enter 
            s = read_adc();
            delay_ms(50);//*************************
            }
    if(s > 195 && s < 225)
           goto CONF_MAX; //enter cuando no se elige configurar el sistema 
           
    if(s > 115 && s < 135){// pulsa la tecla izquierda
           glcd_rect(9,38,42,57,NO,OFF);
           glcd_rect(47,38,80,57,NO,ON);
           glcd_rect(85,38,118,57,NO,ON);
           delay_ms(50);
           goto TEMP1;
       }   
     else if(s > 165 &&  s < 185){ // derecha
           RET:
           glcd_rect(9,38,42,57,NO,ON);
           glcd_rect(47,38,80,57,NO,ON);
           glcd_rect(85,38,118,57,NO,OFF);
           delay_ms(100);
           s = read_adc();
           delay_us(40);
           while(s > 240){
           s = read_adc();
           delay_ms(50);//**
            }
        if(s > 195 && s < 225) //enter
           goto INICIO;
        else if(s > 115 && s < 135)
               goto Returno;
        else if(s > 165 &&  s < 185)
               goto RET;
     }
       else 
           goto TEMP1;
   }goto TEMP1;
   
 
   

  CONF_MINI:
  
         glcd_fillScreen(0);
         glcd_rect(0,0,127,63,NO,ON);
         glcd_rect(1,1,126,62,NO,ON);
         glcd_text57(22,5,TEMP_MIN, 1, 1);
         sprintf(Pgeneral2,"%02d°C ",tempminima);
         glcd_text57(20,18,Pgeneral2, 2, 1);//aumenta el tamaño del texto de la funcion 
         
         glcd_rect(20,34,40,35,YES,ON);         //   linea que selecciona LA HORA
         glcd_rect(8,40,119,58,YES,ON);         //      recuadro
         glcd_text57(34,46,ESTABLECER, 1, 0);   //
         
         tempset=tempminima;
         
      STARTMIN:
      
         glcd_rect(20,34,40,35,YES,ON);
         glcd_rect(52,34,73,35,YES,OFF); 
         glcd_rect(85,34,107,35,YES,OFF);
         
             glcd_rect(9,41,118,57,NO,ON);
             s = read_adc();    
             delay_ms(50);
   
   
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
             }
             if (s > 10 && s < 40){ // tecla arriba cuadrar hora
                 
                 if(tempset > 99 )
                     tempset = 99;
                 tempset ++;
                 
                 glcd_rect(20,18,40,32,YES,OFF);
                 sprintf(Pgeneral2,"%02d",tempset);
                 glcd_text57(20,18,Pgeneral2, 2, 1);
                 delay_ms(100);
                 goto STARTMIN;
             }
            else if(s > 60 && s < 90){
                 
                 if(tempset < 1 )
                     tempset = 1;
                 tempset --;
                 glcd_rect(20,18,40,32,YES,OFF);
                 sprintf(Pgeneral2,"%02d",tempset);
                 glcd_text57(20,18,Pgeneral2, 2, 1);
                 delay_ms(100);
                 goto STARTMIN;
             }
             
             
      else if(s > 165 &&  s < 185){          
           
             glcd_rect(9,41,118,57,NO,OFF);
             glcd_rect(20,34,40,35,YES,OFF);
             STARTTEMP:
                    delay_ms(200);
                    s = read_adc();    
                    delay_ms(50);
                    while(s>230){
                       s = read_adc();    
                       delay_ms(50);
                    }
                    if(s > 195 && s < 225)
                         goto SET_TEMP;
                    if(s > 115 && s < 135)
                        goto STARTMIN;
                 }
                 else
                     goto STARTTEMP;
               
          
              
                 goto STARTMIN;
          
         


      
      
  CONF_MAX:
   glcd_fillScreen(0);
         glcd_rect(0,0,127,63,NO,ON);
         glcd_rect(1,1,126,62,NO,ON);
         glcd_text57(22,5,TEMP_MAX, 1, 1);
         sprintf(Pgeneral2,"%02d°C ",tempmaxima);
         glcd_text57(20,18,Pgeneral2, 2, 1);//aumenta el tamaño del texto de la funcion 
         
         glcd_rect(20,34,40,35,YES,ON);         //   linea que selecciona LA 
         glcd_rect(8,40,119,58,YES,ON);         //      recuadro
         glcd_text57(34,46,ESTABLECER, 1, 0);   //
         
         tempset2=tempmaxima;
         
      STARTMAX:
      
         glcd_rect(20,34,40,35,YES,ON);
         glcd_rect(52,34,73,35,YES,OFF); 
         glcd_rect(85,34,107,35,YES,OFF);
         
             glcd_rect(9,41,118,57,NO,ON);
             s = read_adc();    
             delay_ms(50);
   
   
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
             }
             if (s > 10 && s < 40){ // tecla arriba cuadrar hora
                 
                 if(tempset2 > 99 )
                     tempset2 = 99;
                 tempset2 ++;
                 
                 glcd_rect(20,18,40,32,YES,OFF);
                 sprintf(Pgeneral2,"%02d",tempset2);
                 glcd_text57(20,18,Pgeneral2, 2, 1);
                 delay_ms(100);
                 goto STARTMAX;
             }
            else if(s > 60 && s < 90){
                 
                 if(tempset2 < 1 )
                     tempset2 = 1;
                 tempset2 --;
                 glcd_rect(20,18,40,32,YES,OFF);
                 sprintf(Pgeneral2,"%02d",tempset2);
                 glcd_text57(20,18,Pgeneral2, 2, 1);
                 delay_ms(100);
                 goto STARTMAX;
             }
             
             
      else if(s > 165 &&  s < 185){          
           
             glcd_rect(9,41,118,57,NO,OFF);
             glcd_rect(20,34,40,35,YES,OFF);
             STARTTEMP2:
                    delay_ms(200);
                    s = read_adc();    
                    delay_ms(50);
                    while(s>230){
                       s = read_adc();    
                       delay_ms(50);
                    }
                    if(s > 195 && s < 225)
                         goto SET_TEMP_MAX;
                    if(s > 115 && s < 135)
                        goto STARTMAX;
                 }
                 else
                     goto STARTTEMP2;
               
          
              
                 goto STARTMAX;
 
  SET_TEMP:
  
        tempminima = tempset;
       
        glcd_fillScreen(0);
  
        glcd_finalizado();
        glcd_text57(45,25,DATOS, 1, 1);
        glcd_text57(45,35,DATOS2, 1, 1);
        delay_ms(3000);
       
        goto  CONF_TEMP;
  SET_TEMP_MAX:
         tempmaxima = tempset2;
        glcd_fillScreen(0);
  
        glcd_finalizado();
        glcd_text57(45,25,DATOS, 1, 1);
        glcd_text57(45,35,DATOS2, 1, 1);
        delay_ms(3000);
         
        goto  CONF_TEMP;
        
    CONF_RIEGO:
    
         glcd_fillScreen(0);
         glcd_rect(0,0,127,63,NO,ON);
         glcd_rect(1,1,126,62,NO,ON);
        
         glcd_text57(10,10,CON_RIEGO, 1, 1);
         glcd_rect(5,25,122,39,YES,ON);
         glcd_text57(10,30,NEBULIZACION, 1, 0);
         glcd_rect(5,42,122,56,YES,ON);
         glcd_text57(10,47,GOTEO, 1, 0);
                
     
         glcd_rect(6,26,121,38,NO,OFF); // rectangulo selector 
     RIEGO: 
          s = read_adc();
          delay_ms(100); //***************************
   
        while(s > 240){
          s = read_adc();
          delay_ms(50);
        }
       if(s > 195 && s < 225) //enter
          goto CONF_NEBU;
       else if(s > 60 && s < 90){  // pulsa tecla abajo
            RE:
           glcd_rect(6,26,121,38,NO,ON);
           glcd_rect(6,43,121,55,NO,OFF);
           delay_ms(100);
           s = read_adc();
           delay_us(40);
           
         while(s > 240){
          s = read_adc();
          delay_ms(50);
         }
      if(s > 195 && s < 225) //enter
          goto CONF_GOT;
        
        
         if(s > 60 && s < 90)
         goto RE;
         if( s > 10 && s < 40){
            glcd_rect(6,26,121,38,NO,OFF);
            glcd_rect(6,43,121,55,NO,ON);
         goto RIEGO;
         }
         else goto RE;
       }
       goto RIEGO;
      
         
         
      CONF_NEBU:
      
         glcd_fillScreen(0);
         glcd_rect(0,0,127,63,NO,ON);
         glcd_rect(1,1,126,62,NO,ON);
        
         glcd_text57(10,10,NEBULIZACION, 1, 1);
         glcd_rect(5,25,122,39,YES,ON);
         glcd_text57(10,30,TEMPORIZADO, 1, 0);
         glcd_rect(5,42,122,56,YES,ON);
         glcd_text57(10,47,SENSADO, 1, 0);
         
         glcd_rect(6,26,121,38,NO,OFF); // rectangulo selector 
     SEN: 
          s = read_adc();
          delay_ms(100); //***************************
   
        while(s > 240){
          s = read_adc();
          delay_ms(50);
        }
       if(s > 195 && s < 225) //enter
          goto CONF_TEMPORIZADOR;
       else if(s > 60 && s < 90){  // pulsa tecla abajo
            RE1:
           glcd_rect(6,26,121,38,NO,ON);
           glcd_rect(6,43,121,55,NO,OFF);
           delay_ms(100);
           s = read_adc();
           delay_us(40);
           
         while(s > 240){
          s = read_adc();
          delay_ms(50);
         }
      if(s > 195 && s < 225) //enter
          goto CONF_SENSADO;   
         if(s > 60 && s < 90)
         goto RE1;
         if( s > 10 && s < 40){
            glcd_rect(6,26,121,38,NO,OFF);
            glcd_rect(6,43,121,55,NO,ON);
         goto SEN;
         }
         else goto RE1;
       }
       goto SEN;
      

     CONF_TEMPORIZADOR:
     
       
         glcd_fillScreen(0);
         glcd_rect(0,0,127,63,NO,ON);
         glcd_rect(1,1,126,62,NO,ON);
           
         glcd_rect(3,3,122,18,YES,ON);
         glcd_text57(10,6,TIEMPO_REPOSO, 1, 0);
         glcd_rect(3,20,122,33,YES,ON);
         glcd_text57(10,23,TIEMPO_RIEGO, 1, 0);
         glcd_rect(3,35,122,46,YES,ON);
         glcd_text57(10,38,NUM_CICLOS, 1, 0);
         glcd_rect(3,48,122,60,YES,ON);
         glcd_text57(10,50,DIAS_TRABAJO, 1, 0);
         
         glcd_rect(4,4,121,17,NO,OFF); // rectangulo selector 
        
        TEMPO: 
          s = read_adc();
          delay_ms(100); //***************************
   
        while(s > 240){
          s = read_adc();
          delay_ms(50);
        }
       if(s > 195 && s < 225) //enter
          goto CONF_REPOSO;
       else if(s > 60 && s < 90){  // pulsa tecla abajo
         TEMPO2:
           glcd_rect(4,4,121,17,NO,ON);
           glcd_rect(4,21,121,32,NO,OFF);
           delay_ms(100);
           s = read_adc();
           delay_us(40);
           
         while(s > 240){
          s = read_adc();
          delay_ms(50);
         }
      if(s > 195 && s < 225) //enter
          goto CONF_RIEGO2;
      if(s > 10 && s < 40){
           glcd_rect(4,4,121,17,NO,OFF);
           glcd_rect(4,21,121,32,NO,ON);
         goto TEMPO;
       }
       
      if(s > 60 && s < 90){  // pulsa tecla abajo
         TEMPO3:
           glcd_rect(4,21,121,32,NO,ON);
           glcd_rect(4,36,121,45,NO,OFF);
           delay_ms(100);
           s = read_adc();
           delay_us(40);
           
         while(s > 240){
          s = read_adc();
          delay_ms(50);
         }
      if(s > 195 && s < 225) //enter
          goto CONF_NUMERO;
      if(s > 10 && s < 40){
       glcd_rect(4,36,121,45,NO,ON);
          goto TEMPO2;
      }
      if(s > 60 && s < 90){  // pulsa tecla abajo
            TEMPO4:
            
           glcd_rect(4,49,121,59,NO,OFF);
           glcd_rect(4,36,121,45,NO,ON);
           delay_ms(100);
           s = read_adc();
           delay_us(40);
           
         while(s > 240){
          s = read_adc();
          delay_ms(50);
         }
      if(s > 195 && s < 225) //enter
          goto CONF_DIAS;
      if(s > 10 && s < 40){
       glcd_rect(4,49,121,59,NO,ON);
          goto TEMPO3;
      }
      else goto TEMPO4; 
         
         }
        } 
       }goto TEMPO;

        

     CONF_REPOSO:
     
       glcd_fillScreen(0);
       glcd_rect(0,0,127,63,NO,ON);
       glcd_rect(1,1,126,62,NO,ON);
       glcd_text57(22,5,TIEMPO_REPOSO, 1, 1);
       sprintf(Pgeneral5,"%02d",repos);
       glcd_text57(30,18,Pgeneral5, 2, 1);   //   linea que selecciona LA HORA
       glcd_text57(56,18,h, 2, 1);
       
      
       glcd_rect(8,40,119,58,YES,ON);         //      recuadro
       glcd_text57(34,46,ESTABLECER, 1, 0);   //
       
       reposset = repos;
       
   START40:
   
        glcd_rect(30,34,50,35,YES,ON);  
        glcd_rect(55,34,65,35,YES,ON);
      
        glcd_rect(52,34,73,35,YES,OFF); 
        glcd_rect(85,34,107,35,YES,OFF);
     
        glcd_rect(9,41,118,57,NO,ON);
             s = read_adc();    
             delay_ms(50);
   
   
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
             }
             if (s > 10 && s < 40){ // tecla arriba cuadrar hora
                 
                 if(reposset > 99){
                     reposset = 99;}
                 reposset ++;
                 
                 glcd_rect(30,18,50,32,YES,OFF);// linea
                 sprintf(Pgeneral5,"%02d", reposset);
                 glcd_text57(30,18,Pgeneral5, 2, 1);
                 delay_ms(100);
                 goto START40;
             }
               else if(s > 60 && s < 90){
                 
                 if(reposset < 1 )
                     reposset = 1;
                 reposset --;
                 glcd_rect(30,18,50,32,YES,OFF);
                 sprintf(Pgeneral5,"%02d", reposset);
                 glcd_text57(30,18,Pgeneral5, 2, 1);
                 delay_ms(100);
                 goto START40;
             }
         else if(s > 165 &&  s < 185){
         
         START60:
                 
                glcd_rect(30,34,50,35,YES,OFF);  
                glcd_rect(55,34,65,35,YES,ON);
               
                 
                 delay_ms(200);
                 s = read_adc();    
                 delay_ms(50);
                 while(s>230){
                   s = read_adc();    
                   delay_ms(50);
                   }
                  if (s > 10 && s < 40){
                     
                     tim = 1;
                     glcd_text57(56,18,m, 2, 0);
                     glcd_rect(55,34,65,35,YES,ON);
                     glcd_text57(56,18,h, 2, 1);
                     goto START60;
                  }
                  
                   if (s > 60 && s < 90){
                     
                     tim = 0;
                     glcd_text57(56,18,h, 2, 0);
                     glcd_rect(55,34,65,35,YES,ON);
                     glcd_text57(56,18,m, 2, 1);
                     goto START60;
                  }
                  if(s > 115 && s < 135){
                    glcd_rect(30,34,50,35,YES,ON);
                    glcd_rect(55,34,65,35,YES,OFF);
                        goto START40;}
                 
                 
                 if(s > 165 &&  s < 185){
                 
                  START70:
                    glcd_rect(55,34,65,35,YES,OFF);
                    glcd_rect(9,41,118,57,NO,OFF);
                   
                    delay_ms(200);
                    s = read_adc();    
                    delay_ms(50);
                    while(s>230){
                       s = read_adc();    
                       delay_ms(50);
                    }
                    if(s > 195 && s < 225)
                        goto SET_REPOSO;
                        
                    if(s > 115 && s < 135){
                     glcd_rect(55,34,65,35,YES,ON);
                     glcd_rect(9,41,118,57,NO,ON);
                        goto START60;
                 }   
                   else goto START70;
                 }
                 else
                     goto START70;
             }  
                   
             else 
                 goto START40;
            
     SET_REPOSO:
         
         repos = reposset;
         goto CONF_TEMPORIZADOR;
       
     CONF_RIEGO2:
     
     
     
       glcd_fillScreen(0);
       glcd_rect(0,0,127,63,NO,ON);
       glcd_rect(1,1,126,62,NO,ON);
       glcd_text57(22,5,TIEMPO_RIEGO, 1, 1);
       sprintf(Pgeneral5,"%02d",rieg);
       glcd_text57(30,18,Pgeneral5, 2, 1);   //   linea que selecciona LA HORA
       glcd_text57(56,18,h, 2, 1);
       
      
       glcd_rect(8,40,119,58,YES,ON);         //      recuadro
       glcd_text57(34,46,ESTABLECER, 1, 0);   //
       
       riegset = rieg;
       
   STARTRIEGO:
   
        glcd_rect(30,34,50,35,YES,ON);  
        glcd_rect(55,34,65,35,YES,ON);
      
        glcd_rect(52,34,73,35,YES,OFF); 
        glcd_rect(85,34,107,35,YES,OFF);
     
        glcd_rect(9,41,118,57,NO,ON);
             s = read_adc();    
             delay_ms(50);
   
   
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
             }
             if (s > 10 && s < 40){ // tecla arriba cuadrar hora
                 
                 if(riegset > 99){
                     riegset = 99;}
                 riegset ++;
                 
                 glcd_rect(30,18,50,32,YES,OFF);// linea
                 sprintf(Pgeneral5,"%02d", riegset);
                 glcd_text57(30,18,Pgeneral5, 2, 1);
                 delay_ms(100);
                 goto STARTRIEGO;
             }
               else if(s > 60 && s < 90){
                 
                 if(riegset < 1 )
                     riegset = 1;
                 riegset --;
                 glcd_rect(30,18,50,32,YES,OFF);
                 sprintf(Pgeneral5,"%02d", riegset);
                 glcd_text57(30,18,Pgeneral5, 2, 1);
                 delay_ms(100);
                 goto STARTRIEGO;
             }
         else if(s > 165 &&  s < 185){
         
         STARTRIEGO1:
                 
                glcd_rect(30,34,50,35,YES,OFF);  
                glcd_rect(55,34,65,35,YES,ON);
               
                 
                 delay_ms(200);
                 s = read_adc();    
                 delay_ms(50);
                 while(s>230){
                   s = read_adc();    
                   delay_ms(50);
                   }
                  if (s > 10 && s < 40){
                     
                     tim2 = 1;
                     glcd_text57(56,18,m, 2, 0);
                     glcd_rect(55,34,65,35,YES,ON);
                     glcd_text57(56,18,h, 2, 1);
                     goto STARTRIEGO1;
                  }
                  
                   if (s > 60 && s < 90){
                     
                     tim2 = 0;
                       glcd_text57(56,18,h, 2, 0);
                     glcd_rect(55,34,65,35,YES,ON);
                     glcd_text57(56,18,m, 2, 1);
                     goto STARTRIEGO1;
                  }
                  if(s > 115 && s < 135){
                    glcd_rect(30,34,50,35,YES,ON);
                    glcd_rect(55,34,65,35,YES,OFF);
                        goto STARTRIEGO;}
                 
                 
                 if(s > 165 &&  s < 185){
                 
                  STARTRIEGO2:
                    glcd_rect(55,34,65,35,YES,OFF);
                    glcd_rect(9,41,118,57,NO,OFF);
                   
                    delay_ms(200);
                    s = read_adc();    
                    delay_ms(50);
                    while(s>230){
                       s = read_adc();    
                       delay_ms(50);
                    }
                    if(s > 195 && s < 225)
                        goto CONF_TEMPORIZADOR;
                        
                    if(s > 115 && s < 135){
                     glcd_rect(55,34,65,35,YES,ON);
                     glcd_rect(9,41,118,57,NO,ON);
                        goto STARTRIEGO1;
                 }   
                   else goto STARTRIEGO2;
                 }
                 else
                     goto STARTRIEGO2;
             }  
                   
             else 
                 goto STARTRIEGO;
         
     CONF_NUMERO:
     
       glcd_fillScreen(0);
       glcd_rect(0,0,127,63,NO,ON);
       glcd_rect(1,1,126,62,NO,ON);
       glcd_text57(22,5,NUM_CICLOS, 1, 1);
       sprintf(Pgeneral5,"%02d",num);
       glcd_text57(30,18,Pgeneral5, 2, 1);   //   linea que selecciona LA HORA
       glcd_text57(55,18,CICLOS, 2, 1);
       
      
       glcd_rect(8,40,119,58,YES,ON);         //      recuadro
       glcd_text57(34,46,ESTABLECER, 1, 0);   //
       
       numset = num;
       
   STARTNUM:
   
        glcd_rect(30,34,50,35,YES,ON);  
        glcd_rect(55,34,65,35,YES,ON);
      
        glcd_rect(52,34,73,35,YES,OFF); 
        glcd_rect(85,34,107,35,YES,OFF);
     
        glcd_rect(9,41,118,57,NO,ON);
             s = read_adc();    
             delay_ms(50);
   
   
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
             }
             if (s > 10 && s < 40){ // tecla arriba cuadrar hora
                 
                 if(numset > 99){
                     numset = 99;}
                 numset ++;
                 
                 glcd_rect(30,18,50,32,YES,OFF);// linea
                 sprintf(Pgeneral5,"%02d", numset);
                 glcd_text57(30,18,Pgeneral5, 2, 1);
                 delay_ms(100);
                 goto STARTNUM;
             }
               else if(s > 60 && s < 90){
                 
                 if(numset < 1 )
                     numset = 1;
                 numset --;
                 glcd_rect(30,18,50,32,YES,OFF);
                 sprintf(Pgeneral5,"%02d", numset);
                 glcd_text57(30,18,Pgeneral5, 2, 1);
                 delay_ms(100);
                 goto STARTNUM;
             }
           
                 
             else    if(s > 165 &&  s < 185){
                 
                  STARTNUM1:
                    glcd_rect(30,34,50,35,YES,OFF); 
                    
                    glcd_rect(9,41,118,57,NO,OFF);
                   
                    delay_ms(200);
                    s = read_adc();    
                    delay_ms(50);
                    while(s>230){
                       s = read_adc();    
                       delay_ms(50);
                    }
                    if(s > 195 && s < 225)
                        goto CONF_TEMPORIZADOR;
                        
                    if(s > 115 && s < 135){
                     glcd_rect(55,34,65,35,YES,ON);
                     glcd_rect(9,41,118,57,NO,ON);
                        goto STARTNUM;
                 }   
                   else goto STARTNUM1;
                 }
                 else
                     goto STARTNUM;
           
                   

     CONF_DIAS:
     
     
       glcd_fillScreen(0);
       glcd_rect(0,0,127,63,NO,ON);
       glcd_rect(1,1,126,62,NO,ON);
       glcd_text57(10,5,DIAS_TRABAJO, 1, 1);

       glcd_text57(10,18,LUNES, 2, 1);   //   
 
       
      
       glcd_rect(8,40,70,58,YES,ON);         //      recuadro
       glcd_text57(10,46,ESTABLECER, 1, 0);   //
       
       diasset = dias;
       
   STARTDIAS:
   
        glcd_rect(8,34,80,35,YES,ON);  
        
             s = read_adc();    
             delay_ms(50);
   
   
             while(s>230){
                   s = read_adc();    
                   delay_ms(50);
             }
           if (s > 10 && s < 40){ // tecla arriba cuadrar hora
                 
                 if(diasset > 7){
                     diasset = 7;}
                 diasset ++;
                 
                 glcd_rect(8,18,80,32,YES,OFF);// 

                 
                      if(diasset == 7)
                        glcd_text57(10,18,DOMING, 2, 1);
                      if(diasset == 1)
                        glcd_text57(10,18,LUNES, 2, 1);
                      if(diasset == 2)
                        glcd_text57(10,18,MARTES, 2, 1);
                      if(diasset == 3)
                        glcd_text57(10,18,MIERCO,2, 1);
                      if(diasset == 4)
                        glcd_text57(10,18,JUEVES, 2, 1);
                      if(diasset == 5)
                        glcd_text57(10,18,VIERNE, 2, 1);
                      if(diasset == 6)
                        glcd_text57(10,18,SABADO, 2, 1);
                 
                 goto STARTDIAS;
             }
               else if(s > 60 && s < 90){
                 
                 if(diasset < 1 )
                     diasset = 1;
                 diasset --;
                 glcd_rect(8,18,80,32,YES,OFF);

                 
                      if(diasset == 7)
                        glcd_text57(10,18,DOMING, 2, 1);
                      if(diasset == 1)
                        glcd_text57(10,18,LUNES, 2, 1);
                      if(diasset == 2)
                        glcd_text57(10,18,MARTES, 2, 1);
                      if(diasset == 3)
                        glcd_text57(10,18,MIERCO,2, 1);
                      if(diasset == 4)
                        glcd_text57(10,18,JUEVES, 2, 1);
                      if(diasset == 5)
                        glcd_text57(10,18,VIERNE, 2, 1);
                      if(diasset == 6)
                        glcd_text57(10,18,SABADO, 2, 1);
                 goto STARTDIAS;
             }
             if(s > 195 && s < 225){
                  
                      if(diasset == 7)
                        glcd_text57(110,40,D, 1, 1);
                      if(diasset == 1)
                        glcd_text57(90,15,LU, 1, 1);  
                      if(diasset == 2)
                        glcd_text57(90,23,MA, 1, 1);
                      if(diasset == 3)
                        glcd_text57(90,31,MI,1, 1);
                      if(diasset == 4)
                        glcd_text57(110,15,JU, 1, 1);
                      if(diasset == 5)
                        glcd_text57(110,23,VI, 1, 1);
                      if(diasset == 6)
                        glcd_text57(110,32,SA, 1, 1);
                 goto STARTDIAS;
                 
 
             }
   
             else    if(s > 165 &&  s < 185){
                 
                  STARTDIAS1:
                  
                    glcd_rect(8,34,80,35,YES,OFF);  
                    
                    glcd_rect(9,41,118,57,NO,OFF);
                   
                    delay_ms(200);
                    s = read_adc();    
                    delay_ms(50);
                    while(s>230){
                       s = read_adc();    
                       delay_ms(50);
                    }
                    if(s > 195 && s < 225)
                        goto CONF_TEMPORIZADOR;
                        
                    if(s > 115 && s < 135){
                     
                     
                     glcd_rect(8,34,80,35,YES,ON); 
                     glcd_rect(9,41,118,57,NO,ON);
                        goto STARTDIAS;
                 }   
                   else goto STARTDIAS;
                 }
                 else
                     goto STARTDIAS;
        SISTEMA:
        
         
           
             
            glcd_fillScreen(0);
            glcd_rect(0,0,127,63,NO,ON);
            glcd_rect(1,1,126,62,NO,ON);
            
 
            
            temp = ds1820_read();  //funcion
            sprintf(Pgeneral6,"%.1f °C",temp);
            glcd_text57(80,18,Pgeneral6, 1, 1);
            
        INICIO_SISTEMA:
            glcd_fillScreen(0);
            delay_ms(1000);
            leerRTC();

            sprintf(Pgeneral5,"\%02d:\%02d:\%02d", hr,min,sec);
            glcd_text57(70,33,Pgeneral5, 1, 1);
    
          // glcd_rect(69,33,120,50,NO,ON);

            //sprintf(Pgeneral,"\%02d/\%02d/\%02d", dia,mes,yr);
            //glcd_text57(76,53,Pgeneral, 1, 1);
            //tim = 1 horas tim= 0 minutos
           //if( NIVEL== 1){
               
            
              // if(tim ==1){
               
               
               
              // }
            
            
            
            //}
            
            
goto INICIO_SISTEMA;
     CONF_GOT:
         glcd_fillScreen(0);
         glcd_rect(0,0,127,63,NO,ON);
         glcd_rect(1,1,126,62,NO,ON);
         
     CONF_SENSADO:
         glcd_fillScreen(0);
         glcd_rect(0,0,127,63,NO,ON);
         glcd_rect(1,1,126,62,NO,ON);
         

     
      
    }
    
