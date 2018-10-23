#include <string>
#include <iostream>
#include <iterator>

/* =================== Declaração das Funções =================== */

int tam_tipo (std::string txt);

int tam_funcao(std::string txt);

int tam_param(std::string txt);

int tam_id(std::string txt);

bool programa(std::string txt_original);

bool listadeFuncoes(std::string txt_original);

/* =================== Funções Auxiliares =================== */

int tam_tipo (std::string txt){
  std::string tipos[] = {"int", "pf", "logico", "texto"};
  int tam_vetor = 0;
  for (int i = 0; i < 4; i++) {
    if ((txt.substr(0,6)).find(tipos[i]) > 0) {
      txt.erase(0,tipos[i].size());
      tam_vetor = tipos[i].size();
      break;
    }
  }
  if (tam_vetor!=0) {
    return tam_vetor;
  }
  return -1;
}

std::string str_retorno(std::string txt) {
  int i;
  std::size_t pos = txt.find("retorno");
  if (pos == -1) {
    return '';
  }
  for(i=0; txt[pos+i] != ";" && txt[pos+i] != *txt.end(), i++);
  if(txt[pos+i] == *txt.end()) {
    return '';
  }
  return txt.substr(pos, i);
}

int tam_funcao(std::string txt){  // Pega a posição final i da função no txt baseado nas chaves.
  int cont_chaves = 1;
  int i = 0;

  if (txt[i] == '{') {
    i++;
    for(std::string::iterator it=txt.begin()+1; it!=txt.end() && cont_chaves!=0; it++) {
      if(*it == '{') {
        cont_chaves++;
      }
      if(*it == '}') {
        cont_chaves--;
      }
      i++;
    }
    if (cont_chaves!=0) {
      return -1;
    }
    return i;
  }
  else {
    if (txt[i] == *txt.end()) {
      return 0;
    }
    else {
      return -1;
    }
  }
}

int tam_param(std::string txt){  // Pega a posição final i da expressao no txt baseado nos parenteses.
  int cont_parenteses = 0;
  int i = 0;
  if(txt[i] == '(') {
    i++;
    cont_parenteses++;
    for(; txt[i] != *txt.end() && cont_parenteses != 0; i++) {
      if (txt[i] == '(') {
        cont_parenteses++;
      }
      if (txt[i] == ')') {
        cont_parenteses--;
      }
    }
    if (cont_parenteses!=0) {
      return -1;
    }
    return i;
  }
  else {
    return -1;
  }
}

int tam_id(std::string txt) {
  int i=0;
  for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='('; it++) {
    i++;
  }
  if(txt[i]==*txt.end()) {
    return -1;
  }
  return i;
}

/* =================== Reconhecedor =================== */

// Reconhecedor da transformação <programa>.
bool programa(std::string txt_original) {
  // Começa com principal?
  txt = txt_original;
  if(txt.compare(0,9,"principal") == 0) {
    txt.erase(0,9);
    // Pega a lista de comandos.
    int tam_programa = tam_funcao(txt);
    if (tam_programa < 0) {
      return false;
    }
    if (*txt.end() == txt[tam_programa]) {
      return listadeComandos(txt.substr(0,tam_programa));
    }
    else {
      return listadeComandos(txt.substr(0,tam_programa)) && listadeFuncoes(txt.substr(tam_programa));
    }
  }
  else {
    return false;
  }
}

// Reconhecedor da transformação <ListadeFunções>.
bool listadeFuncoes(std::string txt_original) {

  // Verifica qual o tipo de retorno da função.
  std::string txt = txt_original;
  if(txt.compare(0,3, "int") == 0) {
    txt.erase(0,3);

    return funcaoretorno(txt);
  }
  if(txt.compare(0,2, "pf") == 0) {
    txt.erase(0,2);

    return funcaoretorno(txt);
  }
  if(txt.compare(0,6, "logico") == 0) {
    txt.erase(0,6);

    return funcaoretorno(txt);
  }
  if(txt.compare(0,5, "texto") == 0) {
    txt.erase(0,5);

    return funcaoretorno(txt);
  }
  if(txt.compare(0,5, "vetor") == 0) {
    txt.erase(0,5);

    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    txt.erase(0,tam_t);

    return tipo(t) && funcaoretorno(txt);
  }
  if(txt.compare(0,6, "matriz") == 0) {
    txt.erase(0,6);

    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    txt.erase(0,tam_t);

    return tipo(t) && funcaoretorno(txt);
  }
  else {
    // Pega o identificador.
    int i = 0;
    if (!std::isalpha(*txt.begin())) {
      return false;
    }

    int tam_i = tam_id(txt);
    std::string letras = txt.substr(0, tam_i);
    txt.erase(0, tam_i);

    // Pega a lista de parâmetros.
    int tam_p = tam_param(txt);
    if (tam_p < 0) {
      return false;
    }
    std::string parametros = txt.substr(0, tam_p);
    txt.erase(0,tam_p);

    // Pega a lista de comandos (tamanho da função).
    int tam_f = tam_funcao(txt);
    if (tam_f < 0) {
          return false;
    }
    if (txt[tam_f] == *txt.end()) {
      return letra(letras) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2);
    }
    else {
      return letra(letras) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2) && listadeFuncoes(txt.substr(tam_f));
    }
  }
}

bool funcaoretorno(std::string txt) {
  // Pega o retorno.
  std::string retorno = str_retorno(txt);
  if (retorno == '') {
    return false;
  }
  txt.erase(txt.find(retorno), retorno.size());

  // Pega o identificador.
  int tam_i = tam_id(txt)
  std::string id = txt.substr(0, tam_i);
  txt.erase(0, tam_i);

  // Pega a lista de parâmetros.
  int tam_p = tam_param(txt);
  if (tam_p < 0) {
    return false;
  }
  std::string parametros = txt.substr(0, tam_param);
  txt.erase(0,tam_param);

  // Pega a lista de comandos (tamanho da função).
  int tam_f = tam_funcao(txt);
  if (tam_f < 0) {
    return false;
  }

  // Deriva.
  if (tam_f == 0) {
    return identificador(id) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2) && comandodeRetorno(retorno);
  }
  else {
    return identificador(id) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2) && comandodeRetorno(retorno) && listadeFuncoes(txt.substr(tam_f));
  }
}

bool listadeParametros(std::string txt) {
  if(txt.compare(0,1, '(') == 0) {
    txt.erase(0);
  }
  if (txt.compare(0,1, ')') == 0) {
    return true;
  }
  int i = 0;
  for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!=','; it++) {
    i++;
  }

  //  Caso so tenha um parametro deriva em Parametro.
  if (txt[i] == ')') {
    return parametro(txt.substr(0,i-1));
  }

  //  Deriva em Parametro listadeParametros_.
  return parametro(txt.substr(0,i-1)) && listadeParametros_(txt.substr(i,txt.end()-1));

}

bool listadeParametros_(std::string txt) {
  // Pega a virgula.
  if(txt[0] == ',') {
    txt.erase(0,1);
  }
  else {
    return false;
  }

  int i=0;
  for (std::string::iterator it=i; it!=txt.end() && *it!=','; it++) {
    i++;
  }

  //  Deriva em Parametro listadeParametros_.
  if(txt[i] == ',') {
    return parametro(txt.substr(0,i-1)) && listadeParametros_(txt.substr(i));
  }

  //  Caso so tenha um parametro deriva em Parametro.
  else {
    return parametro(txt);
  }
}

bool parametro(std::string txt) {

  int tam_tipo = tam_tipo(txt);
  // No caso da existencia no inicio de um Tipo: deriva em Tipo e Identificador.
  if (tam_tipo>0) {
    return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, txt.end())));

  } else {
    if(txt.compare(0,5, "vetor") == 0) {
      txt.erase(0,5);
      int tam_tipo = tam_tipo(txt);
      // Deriva para caso exista um Tipo
      if (tam_tipo>0) {
        // Encontra o Identificador
        int j = tam_tipo;
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Tipo Identificador;
        if (j==txt.end()) {
          return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo,txt.end())));
        }

        // Encontra o Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }
        //  Deriva em Tipo Identificador [Valor_Inteiro];
        return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, j)) && valor_inteiro(txt.substr(j+2, k)));

      // Deriva para caso não exista um Tipo
      } else {
        int pos_como = txt.find("como");
        int j = pos_como+4;
        // Encontra o Identificador
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Identificador como Identificador;
        if (j==txt.end()) {
          return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,txt.end())));
        }

        // Encontra o Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }
        //  Deriva em Identificador como Identificador[Valor_Inteiro];
        return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,j)) && valor_inteiro(txt.substr(j+2, k)));
      }
    }
    if(txt.compare(0,6, "matriz") == 0) {
      txt.erase(0,6);
      int tam_tipo = tam_tipo(txt);
      // Deriva para caso exista um Tipo
      if (tam_tipo>0) {
        // Encontra o Identificador
        int j = tam_tipo;
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Tipo Identificador;
        if (j==txt.end()) {
          return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo,txt.end())));
        }

        // Encontra o primeiro Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }

        // Encontra o segundo Valor_Inteiro
        int x = k+3;
        for(std::string::iterator it=k+3; it!=txt.end() && *it!=']'; it++) {
          x++;
        }

        //  Deriva em Tipo Identificador [Valor_Inteiro];
        return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, j)) && valor_inteiro(txt.substr(j+2, k)) && valor_inteiro(txt.substr(k+3, x)));

      // Deriva para caso não exista um Tipo
      } else {
        int pos_como = txt.find("como");
        int j = pos_como+4;
        // Encontra o Identificador
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Identificador como Identificador;
        if (j==txt.end()) {
          return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,txt.end())));
        }

        // Encontra o primeiro Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }

        // Encontra o segundo Valor_Inteiro
        int x = k+3;
        for(std::string::iterator it=k+3; it!=txt.end() && *it!=']'; it++) {
          x++;
        }

        //  Deriva em Identificador como Identificador[Valor_Inteiro][Valor_Inteiro];
        return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,j)) && valor_inteiro(txt.substr(j+2, k)) && valor_inteiro(txt.substr(k+3, x)));
      }
    }
  }


}

bool comandodeRetorno(std::string txt) {
  if (txt.compare(0,8,"retorno=")) {
    txt.erase(0,8);
    return expressao(txt.substr(txt.begin(), txt.end()-1));
  }
  else {
    return false;
  }
}

bool listadeComandos(std::string txt) {
  if (txt[0] = '{') {
    txt.erase(0,1);
  } else{
    return false
  }
  return listadeComandos_(txt.substr(0, txt.end()-1));
}

bool listadeComandos_(std::string txt) {
  int i = 0;
  for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!=';'; it++) {
    i++;
  }
  if (txt[i] == *txt.end()) {
    return false;
  }

  return (comando(txt.substr(0, i-1)) && listadeComandos_(txt.substr(i+1,txt.end()));

}

bool comando(std::string txt) {


  int tam_tipo = tam_tipo(txt);
  // No caso da existencia no inicio de um Tipo: deriva em Tipo e Identificador.
  if (tam_tipo>0) {
    return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, txt.end())));

  } else {
    if(txt.compare(0,5, "vetor") == 0) {
      txt.erase(0,5);
      int tam_tipo = tam_tipo(txt);
      // Deriva para caso exista um Tipo
      if (tam_tipo>0) {
        // Encontra o Identificador
        int j = tam_tipo;
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Tipo Identificador;
        if (j==txt.end()) {
          return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo,txt.end())));
        }

        // Encontra o Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }
        //  Deriva em Tipo Identificador [Valor_Inteiro];
        return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, j)) && valor_inteiro(txt.substr(j+2, k)));

      // Deriva para caso não exista um Tipo
      } else {
        int pos_como = txt.find("como");
        int j = pos_como+4;
        // Encontra o Identificador
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Identificador como Identificador;
        if (j==txt.end()) {
          return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,txt.end())));
        }

        // Encontra o Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }
        //  Deriva em Identificador como Identificador[Valor_Inteiro];
        return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,j)) && valor_inteiro(txt.substr(j+2, k)));
      }
    }
    if(txt.compare(0,6, "matriz") == 0) {
      txt.erase(0,6);
      int tam_tipo = tam_tipo(txt);
      // Deriva para caso exista um Tipo
      if (tam_tipo>0) {
        // Encontra o Identificador
        int j = tam_tipo;
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Tipo Identificador;
        if (j==txt.end()) {
          return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo,txt.end())));
        }

        // Encontra o primeiro Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }

        // Encontra o segundo Valor_Inteiro
        int x = k+3;
        for(std::string::iterator it=k+3; it!=txt.end() && *it!=']'; it++) {
          x++;
        }

        //  Deriva em Tipo Identificador [Valor_Inteiro];
        return (tipo(txt.substr(0,tam_tipo)) && identificador(txt.substr(tam_tipo, j)) && valor_inteiro(txt.substr(j+2, k)) && valor_inteiro(txt.substr(k+3, x)));

      // Deriva para caso não exista um Tipo
      } else {
        int pos_como = txt.find("como");
        int j = pos_como+4;
        // Encontra o Identificador
        for(std::string::iterator it=tam_tipo; it!=txt.end() && *it!='['; it++) {
          j++;
        }

        //  Deriva em Identificador como Identificador;
        if (j==txt.end()) {
          return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,txt.end())));
        }

        // Encontra o primeiro Valor_Inteiro
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!=']'; it++) {
          k++;
        }

        // Encontra o segundo Valor_Inteiro
        int x = k+3;
        for(std::string::iterator it=k+3; it!=txt.end() && *it!=']'; it++) {
          x++;
        }

        //  Deriva em Identificador como Identificador[Valor_Inteiro][Valor_Inteiro];
        return (identificador(txt.substr(0,pos_como-1)) && identificador(txt.substr(pos_como+4,j)) && valor_inteiro(txt.substr(j+2, k)) && valor_inteiro(txt.substr(k+3, x)));
      }
    }
    if(txt.compare(0,8, "Complexo") == 0) {
      txt.erase(0,8);
      int j = 0;
      for(std::string::iterator it=txt.begin(); it!=txt.end() && *it!='{'; it++) {
        j++;
      }
      if (j==txt.end()) {
        return false;
      }
      else{
        // Encontra a lista de declarações.
        int k = j+2;
        for(std::string::iterator it=j+2; it!=txt.end() && *it!='}'; it++) {
          k++;
        }
        //  Deriva em Identificador {listadeDeclaracoes}.
        return (identificador(txt.substr(0,j)) && listadeDeclaracoes(txt.substr(j+2, k)));
      }
    }
    // Procura o primeiro caso "como".
    int pos_como = txt.find("como");
    if (pos_como>0) {
      // Deriva no primeiro caso Letra como Identificador.
      return (letra(txt.substr(0, pos_como-1)) && identificador(txt.substr(pos_como+4, txt.end())));
    } else {

      // Procura a igualdade no segundo caso.
      int pos_igualdade = txt.find('=');
      std::string texto = '';

      // Verifica se é igualado a um texto.
      if (txt[pos_igualdade+1] == '"') {
        texto = txt.substr(pos_igualdade+2, txt.end()-1);
      }

      // Procura caso de letras [Valor Inteiro].
      int pos_colchete_1 = txt.find('[');
      if (pos_colchete_1>0) {
        int pos_colchete_2 = txt.substr(pos_colchete_1+1, txt.end()).find('[');

        // Procura caso de letras [Valor Inteiro][Valor_Inteiro].
        if (pos_colchete_2>0) {
          if (texto.size()>0) {


            // Procura caso de letras [Valor Inteiro][Valor_Inteiro] = "texto".
            return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_colchete_2-2)) && valorInteiro(txt.substr(pos_colchete_2+1, pos_igualdade-1)) && texto(texto));
          }


          // Procura caso de letras [Valor Inteiro][Valor_Inteiro] = Expressao.
          return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_colchete_2-2)) && valorInteiro(txt.substr(pos_colchete_2+1, pos_igualdade-1)) && expressao(txt.substr(pos_igualdade+1, txt.end())));
        }
        if (texto.size()>0) {

          // Procura caso de letras [Valor Inteiro] = "texto".
          return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_igualdade-1)) && texto(texto));
        }

        // Procura caso de letras [Valor Inteiro] = Expressao.
        return (letra(txt.substr(0, pos_colchete_1-1)) && valorInteiro(txt.substr(pos_colchete_1+1, pos_igualdade-1)) && expressao(txt.substr(pos_igualdade+1, txt.end())));
      }
      
    }

  }
}

bool chamadadeFuncao(std::string txt) {

}

bool declaracaodeEstrututra(std::string txt) {

}

bool listadeDeclaracoes(std::string txt) {

}

bool declaracao(std::string txt) {

}

bool atribuicao(std::string txt) {

}

bool atribuicaodeEstrututra(std::string txt) {

}

bool atribuicaodeAtributo(std::string txt) {

}

bool listadeCondicionalCaso(std::string txt) {

}

bool listadeIdentificadores(std::string txt) {

}

int tipo(std::string txt) {

}

bool expressao(std::string txt) {

}

bool expressaoLogica(std::string txt) {

}

bool expressaoLogica_(std::string txt) {

}

bool expressaoAritmetica(std::string txt) {

}

bool expressaoAritmetica_(std::string txt) {

}

bool valorReal(std::string txt) {

}

bool valorInteiro(std::string txt) {

}

bool valor(std::string txt) {

}

bool texto(std::string txt) {

}

bool letra(std::string txt) {

}

bool identificador(std::string txt) {
  std::locale loc;
  for(std::string::iterator it=txt.begin(); it!=txt.end(); it++) {
    if (!std::isalpha(*it,loc)) {
      return false;
    }
  }
  return true;
}

int main() {

  // Lê o arquivo passado como: "./exemplo < <nome_do_arquivo>.txt".
  std::string entrada(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());
  entrada.pop_back();

  // Exclui espaços, tabulações e quebras de linhas da string.
  for(std::string::iterator it=entrada.begin(); it!=entrada.end();) {
    if(*it == '\u0020' || *it == '\u000a' ) {
      entrada.erase(it);
    }
    else {
      it++;
    }
  }

  // Retorna a análise da gramática.
  std::cout << programa(entrada) << std::endl;

  return 0;
}
