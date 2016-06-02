/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


import java.util.ArrayList;
import java.util.Arrays;

/**
 * 0 => espaco nao acessivel
 * 1 => espaco ocupado por uma peca
 * 2 => espaco sem peca
 * @author targueriano
 */
public class RestaUm {

    private int[][] estadoInicial = {{0, 0, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 2, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 1, 0, 0}};

    
    private int[][] estadoAtual = {{0, 0, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 1, 0, 0}, {1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 2, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1}, {0, 0, 1, 1, 1, 0, 0}, {0, 0, 1, 1, 1, 0, 0}};
    
    private int[][] estadoFinal = {{0, 0, 2, 2, 2, 0, 0}, {0, 0, 2, 2, 2, 0, 0}, {2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 1, 2, 2, 2},
    {2, 2, 2, 2, 2, 2, 2}, {0, 0, 2, 2, 2, 0, 0}, {0, 0, 2, 2, 2, 0, 0}};

    
    public RestaUm() {

    }

    public int[][] getEstadoFinal() {
        return estadoFinal;
    }

    public void setEstadoFinal(int[][] estadoFinal) {
        this.estadoFinal = estadoFinal;
    }

    public int[][] getEstadoInicial() {
        return estadoInicial;
    }

    public void setEstadoInicial(int[][] estadoInicial) {
        this.estadoInicial = estadoInicial;
    }

    public int[][] getEstadoAtual() {
        return estadoAtual;
    }

    public void setEstadoAtual(int[][] estadoAtual) {
        this.estadoAtual = estadoAtual;
    }

    public int valida(ArrayList<Nodo> I, int[][] estado) {
        for (int k = 0; k < I.size(); k++) {
            if (Arrays.deepEquals(estado, I.get(k).estado)) {
                return -1;
            }
        }
        return 1;
    }

    public void insereNoFinal(Nodo nodo, ArrayList<Nodo> I, ArrayList<Nodo> E) {
        //saltar pedra com lugar vazio
        //up, down, left and right
        //percorrer matriz para buscar lugar vazio = 2
        //imprimir(estado);
        int aux = 0;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (nodo.estado[i][j] == 2) {
                    //System.out.println(i);
                    //System.out.println(j);
                    pulaDireita(i, j, nodo, I, E);
                    pulaEsquerda(i, j, nodo, I, E);
                    pulaDown(i, j, nodo, I, E);
                    pulaUp(i, j, nodo, I, E);
                }
            }
        }
        //estadoInicial = (int[][]) E.get(0);
        System.out.println("######Nova camada#######\n");
    }

    public int pulaDireita(int origemX, int origemY, Nodo nodo, ArrayList<Nodo> I, ArrayList<Nodo> E) {

        if (origemY > 1 && origemY <= 6) {
            if (nodo.estado[origemX][origemY - 1] == 1 && nodo.estado[origemX][origemY - 2] == 1) {
                Nodo filho = new Nodo(nodo);
                filho.estado[origemX][origemY] = 1;
                filho.estado[origemX][origemY - 1] = 2;
                filho.estado[origemX][origemY - 2] = 2;
                //imprimir(estado);
                filho.valor = valor(filho.estado);
                if (valida(I, filho.estado) == 1 && valida(E, filho.estado) == 1) {
                    E.add(filho);
                    return 1;
                }
            }
        }
        return -1;
    }

    public int pulaEsquerda(int origemX, int origemY, Nodo nodo, ArrayList<Nodo> I, ArrayList<Nodo> E) {
    
        if (origemY >= 0 && origemY < 5) {
            if (nodo.estado[origemX][origemY + 1] == 1 && nodo.estado[origemX][origemY + 2] == 1) {
                Nodo filho = new Nodo(nodo);
                filho.estado[origemX][origemY] = 1;
                filho.estado[origemX][origemY + 1] = 2;
                filho.estado[origemX][origemY + 2] = 2;
                filho.valor = valor(filho.estado);
                if (valida(I, filho.estado) == 1 && valida(E, filho.estado) == 1) {
                    E.add(filho);
               
                    return 1;
                }
            }
        }
        return -1;

    }

    public int pulaUp(int origemX, int origemY, Nodo nodo, ArrayList<Nodo> I, ArrayList<Nodo> E) {


        if (origemX >= 0 && origemX < 5) {
            if (nodo.estado[origemX + 1][origemY] == 1 && nodo.estado[origemX + 2][origemY] == 1) {
                Nodo filho = new Nodo(nodo);
                filho.estado[origemX][origemY] = 1; //posicao vazia fica com peca
                filho.estado[origemX + 1][origemY] = 2; //posicao com peca fica vazia
                filho.estado[origemX + 2][origemY] = 2;
                filho.valor = valor(filho.estado);
                if (valida(I, filho.estado) == 1 && valida(E, filho.estado) == 1) {
                    E.add(filho);
      
                    return 1;
                }
            }
        }
        return -1;
    }

    public int pulaDown(int origemX, int origemY, Nodo nodo, ArrayList<Nodo> I, ArrayList<Nodo> E) {

        if (origemX > 1 && origemX <= 6) {
            if (nodo.estado[origemX - 1][origemY] == 1 && nodo.estado[origemX - 2][origemY] == 1) {
                Nodo filho = new Nodo(nodo);
                filho.estado[origemX][origemY] = 1; //posicao vazia fica com peca
                filho.estado[origemX - 1][origemY] = 2; //posicao com peca fica vazia
                filho.estado[origemX - 2][origemY] = 2;
                filho.valor = valor(filho.estado);
                if (valida(I, filho.estado) == 1 && valida(E, filho.estado) == 1) {
                    E.add(filho);
              
                    return 1;
                }
            }
        }
        return -1;
    }

    public void imprimir(int[][] estado) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                System.out.print(estado[i][j] + " ");
            }
            System.out.println("");
        }
        System.out.println("");
    }

    public Nodo removePrimeiro(ArrayList<Nodo> E) {
        Nodo nodoAtual = E.get(0);
        E.remove(0);
        return nodoAtual;
    }

    public void caminho(Nodo nodo) {
        System.out.println("###Meta###");
        Nodo aux = nodo;
        int cont = 0;
        while (aux != null) {
            System.out.println(cont++);
            imprimir(aux.estado);
            aux = aux.pai;
        }
        System.out.println(cont-1 + " movimentos");
    }
    
    //heuristica distancia euclidiana
    public int valor(int[][] estado) { //qto maior o valor, mais distante do estado final está. 
        //A busca é efetuada pelo nodo com menor valor
        int valor = 0;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 7; j++) {
                if (estado[i][j] != estadoFinal[i][j])
                    valor++;
            }
        }
        return valor;
    }
}
