#include <iostream>
#include "Rational.hpp"
#include "SquareMat.hpp"

void menu(){
    int mode = -1;
    std::cout<<"\n\nScegliere cosa fare\n";
    std::cout<<"[1] Calcolare la matrice aggiunta\n[2] Calcolare il determinante\n";
    std::cout<<"[3] Calcolare il prodotto di due matrici\n[4] Calcolare la somma di due matrici\n";
    std::cout<<"[5] Calcolare la trasposta di una matrice\n[6] Calcolare l'inversa di una matrice\n";
    std::cout<<"[7] Verificare se una matrice è ortogonale\n[8] Verificare se una matrice è composta da numeri primi\n";
    std::cout<<"[9] Calcolare il rango di una matrice\n[10] Ridurre una matrice a scalini\n[11] Uscire\n\n";

    std::cin>>mode;

    if (mode < 1 || mode > 11){
        while (mode < 1 || mode > 11){
            std::cout<<"Inserire un numero valido: ";
            std::cin>>mode;
        }
    }

    switch(mode){
        case 1:
        {
            SquareMat m = m.create();

            std::cout<<"Inserisci una riga e una colonna da eliminare (righe e colonne partono da 0).\nRiga: ";
            int row, col;
            std::cin>>row;
            std:: cout<<"Colonna: ";
            std::cin>>col;
            SquareMat red = m.reduce(row, col);

            std::cout<<"Matrice aggiunta:\n";
            red.print();
        }
            break;
        case 2:
        {
            SquareMat m = m.create();

            std::cout<<"Determinante: ";
            m.determinant().print();
            std::cout<<std::endl;
        }
            break;
        case 3:
        {
            SquareMat m = m.create();
            SquareMat p = p.create();

            SquareMat res = m * p;
            std::cout<<"Matrice prodotto:\n";
            res.print();
        }
            break;
        case 4:
        {
            SquareMat m = m.create();
            SquareMat p = p.create();

            SquareMat res = m + p;
            std::cout<<"Matrice somma:\n";
            res.print();
        }
            break;
        case 5:
        {
            SquareMat m = m.create();
            SquareMat tr = m.transpose();
            std::cout<<"Matrice trasposta:\n";
            tr.print();
        }
            break;
        case 6:
        {
            SquareMat m = m.create();
            SquareMat inv = m.inverse();
            std::cout<<"Matrice inversa:\n";
            inv.print();
        }
            break;
        case 7:
        {
            SquareMat m = m.create();
            if (m.orthogonal())
                std::cout<<"La matrice è ortogonale.\n";
            else
                std::cout<<"La matrice non è ortogonale.\n";
        }
            break;
        case 8:
        {
            SquareMat m = m.create();
            if (m.allprimes())
                std::cout<<"La matrice è composta interamente da numeri primi.\n";
            else
                std::cout<<"Nella matrice è presente almeno un numero non primo.\n";
        }
            break;
        case 9:
        {
            SquareMat m = m.create();
            std::cout<<"Rango: "<<m.rank()<<std::endl;
        }
            break;
        case 10:
        {
            SquareMat m = m.create();
            SquareMat meg = m.MEG();
            std::cout<<"Matrice ridotta a scalini:\n";
            meg.print();
        }
            break;
        case 11:
        {
            exit(0);
        }
        default:
            break;
    }
    if (mode != 11) menu();
}

int main() {
	/*
    int dim;
    std::cin >> dim;

    SquareMat m{dim};
    m.read();

    { // es1
        SquareMat x{m};
        x.print();
    }

    { // es 2
        std::cout << m.determinant(); 
    }

    { // es 3
        if (allprimes(m)) {
            std::cout << "tutti primi\n";
        } else {
            std::cout << "almeno un numero non primo\n";
        }
    }
    */

    menu();

    return 0;
}  
