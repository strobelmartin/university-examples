        #include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv)
{
    double a, b, c;
    double alfa_rad, beta_rad, gama_rad;
    int alfa_stup, beta_stup, gama_stup;
    int alfa_min, beta_min, gama_min;
    double obvod, obsah, s;
    double r_veps, r_ops;
    double va, vb, vc;

    printf("Zadejte velikost stran a b c:\n");
    if( (scanf("%lf %lf %lf", &a, &b, &c) != 3) || (a <= 0) || (b <= 0) || (c <= 0) ) {
        printf("Nespravny vstup.\n");
        return 0;
    }
    
    if( (a+b <= c) || (a+c <= b) || (b+c <= a) ) {
        printf("Trojuhelnik neexistuje.\n");
        return 0;
    }

    if( (a==b) || (a==c) || (b==c) ) {
        if( (a==b) && (b==c) ) {
            printf("Trojuhelnik je rovnostranny.\n");
        } else printf("Trojuhelnik je rovnoramenny.\n");
    } else printf("Trojuhelnik neni ani rovnostranny ani rovnoramenny.\n");
          
    alfa_rad = acos( ((a*a) - (b*b) - (c*c)) / (-2 * b * c) );
    beta_rad = acos( ((b*b) - (c*c) - (a*a)) / (-2 * c * a) );
    gama_rad = acos( ((c*c) - (a*a) - (b*b)) / (-2 * a * b) );
    
    alfa_stup = (alfa_rad * 180) / M_PI;
    beta_stup = (beta_rad * 180) / M_PI;
    gama_stup = (gama_rad * 180) / M_PI;
    
    alfa_min = (((alfa_rad * 180) / M_PI)*60) - (alfa_stup*60);
    beta_min = (((beta_rad * 180) / M_PI)*60) - (beta_stup*60);
    gama_min = (((gama_rad * 180) / M_PI)*60) - (gama_stup*60);
    
    if( ( alfa_stup == 90 && alfa_min == 0 && ((((alfa_rad * 180) / M_PI)*3600) - (alfa_stup*3600) - (alfa_min*60)) ) || 
        ( beta_stup == 90 && beta_min == 0 && ((((beta_rad * 180) / M_PI)*3600) - (beta_stup*3600) - (beta_min*60)) ) ||
        ( gama_stup == 90 && gama_min == 0 && ((((gama_rad * 180) / M_PI)*3600) - (gama_stup*3600) - (gama_min*60)) ) ||
        (alfa_rad * 180) / M_PI == 90 || (beta_rad * 180) / M_PI == 90 || (gama_rad * 180) / M_PI == 90 ||
        ((a*a) == (b*b) + (c*c)) || ((b*b) == (a*a) + (c*c)) || ((c*c) == (a*a) + (b*b))
      ) {
        printf("Trojuhelnik je pravouhly.\n");
    } else
        if( (alfa_rad * 180) / M_PI > 90 || (beta_rad * 180) / M_PI > 90 || (gama_rad * 180) / M_PI > 90 ) {
            printf("Trojuhelnik je tupouhly.\n");            
        } else printf("Trojuhelnik je ostrouhly.\n");

    printf("Uhel alfa: %.4f rad = %d s %02d'%05.2f''\n",
            alfa_rad, 
            alfa_stup, 
            alfa_min,
            (((alfa_rad * 180) / M_PI)*3600) - (alfa_stup*3600) - (alfa_min*60)
          );
    printf("Uhel beta: %.4f rad = %d s %02d'%05.2f''\n",
            beta_rad, 
            beta_stup, 
            beta_min,
            (((beta_rad * 180) / M_PI)*3600) - (beta_stup*3600) - (beta_min*60)
          );
    printf("Uhel gama: %.4f rad = %d s %02d'%05.2f''\n",
            gama_rad, 
            gama_stup, 
            gama_min,
            (((gama_rad * 180) / M_PI)*3600) - (gama_stup*3600) - (gama_min*60)
          );
    
    s = (a + b + c) / 2;
    obsah = sqrt( s * (s-a) * (s-b) * (s-c) );
    obvod = a + b + c;
    printf("Obvod: %.4f\n", obvod);
    printf("Obsah: %.4f\n", obsah);
    
    r_veps = obsah / s;
    r_ops = (a * b * c) / (4 * obsah);
    printf("Polomer kruznice vepsane: %.4f\n", r_veps);
    printf("Polomer kruznice opsane: %.4f\n", r_ops);
    
    va = (obsah * 2) / a;
    vb = (obsah * 2) / b;
    vc = (obsah * 2) / c;
    printf("Vyska va: %.4f\n", va);
    printf("Vyska vb: %.4f\n", vb);
    printf("Vyska vc: %.4f\n", vc);

    return (EXIT_SUCCESS);
}
