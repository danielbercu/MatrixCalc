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
    std::cout<<std::endl;

    if (mode < 1 || mode > 11){
        while (mode < 1 || mode > 11){
            std::cout<<"Inserire un numero valido: ";
            std::cin>>mode;
        }
    }

    SquareMat m;

    if (mode != 11){
        try { m.create(); }
        catch(matrix_exception& e){
            if (e.t == matrix_exception::null_matrix)
                std::cout<<"\nMatrice nulla."<<std::endl;
            if (e.t == matrix_exception::invalid_format)
                std::cout<<"\nFormato non valido."<<std::endl;
            menu();
        }
        catch(rational_exception& e){
            std::cout<<"\nAlmeno un numero presenta un formato non valido."<<std::endl;
            menu();
        }
    }

    switch(mode){
        case 1:
        {
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
            std::cout<<"Determinante: ";
            m.determinant().print();
            std::cout<<std::endl;
        }
            break;
        case 3:
        {
            SquareMat p;

            try { p.create(); }
            catch(matrix_exception& e){
                if (e.t == matrix_exception::null_matrix)
                    std::cout<<"\nMatrice nulla."<<std::endl;
                if (e.t == matrix_exception::invalid_format)
                    std::cout<<"\nFormato non valido."<<std::endl;
                menu();
            }
            catch(rational_exception& e){
                std::cout<<"\nAlmeno un numero presenta un formato non valido."<<std::endl;
                menu();
            }

            try{
                SquareMat res = m * p;
                std::cout<<"\nMatrice prodotto:\n";
                res.print();
            }
            catch(matrix_exception& e){
                if (e.t == matrix_exception::impossible_op){
                    std::cout<<"\nDimensioni diverse: impossibile eseguire il prodotto."<<std::endl;
                    menu();
                }
            }
        }
            break;
        case 4:
        {
            SquareMat p;

            try { p.create(); }
            catch(matrix_exception& e){
                if (e.t == matrix_exception::null_matrix)
                    std::cout<<"\nMatrice nulla."<<std::endl;
                if (e.t == matrix_exception::invalid_format)
                    std::cout<<"\nFormato non valido."<<std::endl;
                menu();
            }
            catch(rational_exception& e){
                std::cout<<"\nAlmeno un numero presenta un formato non valido."<<std::endl;
                menu();
            }

            try{
                SquareMat res = m + p;
                std::cout<<"Matrice somma:\n";
                res.print();
            }
            catch(matrix_exception& e){
                if (e.t == matrix_exception::impossible_op){
                    std::cout<<"\nDimensioni diverse: impossibile eseguire la somma."<<std::endl;
                    menu();
                }
            }
        }
            break;
        case 5:
        {
            SquareMat tr = m.transpose();
            std::cout<<"Matrice trasposta:\n";
            tr.print();
        }
            break;
        case 6:
        {
            SquareMat inv = m.inverse();
            std::cout<<"Matrice inversa:\n";
            inv.print();
        }
            break;
        case 7:
        {
            if (m.orthogonal())
                std::cout<<"La matrice è ortogonale.\n";
            else
                std::cout<<"La matrice non è ortogonale.\n";
        }
            break;
        case 8:
        {
            if (m.allprimes())
                std::cout<<"La matrice è composta interamente da numeri primi.\n";
            else
                std::cout<<"Nella matrice è presente almeno un numero non primo.\n";
        }
            break;
        case 9:
        {
            try{
                int rk = m.rank();
                std::cout<<"Rango: "<<rk<<std::endl;
            }
            catch(matrix_exception& e){
                if (e.t == matrix_exception::null_matrix){
                    std::cout<<"\nMatrice nulla."<<std::endl;
                    menu();
                }
            }
        }
            break;
        case 10:
        {
            try{
                SquareMat meg = m.MEG();
                std::cout<<"Matrice ridotta a scalini:\n";
                meg.print();
            }
            catch(matrix_exception& e){
                if (e.t == matrix_exception::null_matrix){
                    std::cout<<"\nMatrice nulla."<<std::endl;
                    menu();
                }
            }
        }
            break;
        case 11:
        {
            exit(0);
        }
        default:
            break;
    }
    if (mode) menu();
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
