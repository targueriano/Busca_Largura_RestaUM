/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */



public class Nodo {
    public Nodo pai;
    public int[][] estado;
    public int valor;
    
    
    public Nodo() {
        
    }
    public Nodo(Nodo pai) {
        this.pai = pai;
        this.estado = new int[pai.estado.length][];
        for (int i = 0; i < this.estado.length; i++) {
            this.estado[i] = pai.estado[i].clone();
        }
    }
    public Nodo(int[][] estado) {
        this.pai = null;
        this.estado = new int[estado.length][];
        for (int i = 0; i < this.estado.length; i++) {
            this.estado[i] = estado[i].clone();
        }
    }

    
    
}
