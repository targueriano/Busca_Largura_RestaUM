/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

/**
 *
 * @author targueriano
 */
public class BuscaLargura {
 
    
    ArrayList<Nodo> I = new ArrayList<>(); //vetor para armazenar os nodos já visitados
    ArrayList<Nodo> E = new ArrayList<>(); //os nodos filhos
    RestaUm resta;
    
    private Nodo nodoAtual;
    
    public int buscaLargura(){
        //estadoAtual = estadoInicial;
        resta = new RestaUm();
        
        E.add(new Nodo(resta.getEstadoAtual()));
        int cont = 0;
        while(!E.isEmpty()){
            System.out.println(cont++);
            nodoAtual = resta.removePrimeiro(E);
            //resta.imprimir(nodoAtual.estado);
            if(Arrays.deepEquals(nodoAtual.estado, resta.getEstadoFinal())){
                  resta.caminho(nodoAtual);
                  return 1;
            }
            
            I.add(nodoAtual); //add o nodo ja analisado
            
            resta.insereNoFinal(nodoAtual,I,E); //insere na fila 
            //ordena conforme o estado mais proximo do final
            Collections.sort(E, (Nodo o1, Nodo o2) -> (resta.valor(o1.estado) - resta.valor(o2.estado))); //heuristica
            
            
        }
        return -1;
                
    }
    
    
    public static void main(String[] args) {
        BuscaLargura bl = new BuscaLargura();
        bl.buscaLargura();
    }
}
