#include <string>
#include <iostream>
#include <iterator>

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

int tam_param(std::string txt){  // Pega a posição final i da expressao no txt baseado nos parenteses.
  int cont_parenteses = 0;
  int i = 0;

  if(txt[i] == '(') {
    i++
    for(std::string::iterator it=txt.begin()+1; it!=txt.end() && cont_parenteses!=0; it++) {
      if(it.compare(0,1,'(') == 0) {
        cont_parenteses++;
      }
      if(it.compare(0,1,')') == 0) {
        cont_parenteses--;
      }
      i++;
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
  if(it==txt.end()) {
    return -1;
  }
  return i;
}

/* =================== Reconhecedor =================== */

// Reconhecedor da transformação <programa>.
bool programa(std::string txt_original) {
  // Começa com principal?
  std::string txt = txt_original;
  if(txt.compare(0,9,"principal") == 0) {
    txt.erase(0,9);
    // Pega a lista de comandos.
    int tam_programa = tam_funcao(txt);
    if (tam_programa < 0) {
      return false;
    }
    if (*txt.end() == txt[tam_programa]) {
      //return listadeComandos(txt.substr(0,tam_programa));
      return true;
    }
    else {
      //return listadeComandos(txt.substr(0,tam_programa)) && listadeFuncoes(txt.substr(tam_programa));
      std::cout << txt.substr(0,tam_programa) << "\n\n=============\n\n";
      return true && listadeFuncoes(txt.substr(tam_programa));
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

    //return funcaoretorno(txt);
    std::cout << txt << "\n\n=============\n\n";
    return true;
  }
  if(txt.compare(0,2, "pf") == 0) {
    txt.erase(0,2);

    //return funcaoretorno(txt);
    std::cout << txt << "\n\n=============\n\n";
    return true;
  }
  if(txt.compare(0,6, "logico") == 0) {
    txt.erase(0,6);

    //return funcaoretorno(txt);
    std::cout << txt << "\n\n=============\n\n";
    return true;
  }
  if(txt.compare(0,5, "texto") == 0) {
    txt.erase(0,5);

    //return funcaoretorno(txt);
    std::cout << txt << "\n\n=============\n\n";
    return true;
  }
  if(txt.compare(0,5, "vetor") == 0) {
    txt.erase(0,5);

    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    txt.erase(0,tam_t);

    //return tipo(t) && funcaoretorno(txt);
    std::cout << t << "\n\n=============\n\n" << txt << "\n\n=============\n\n";
    return true
  }
  if(txt.compare(0,6, "matriz") == 0) {
    txt.erase(0,6);

    // Pega tipo.
    int tam_t = tam_tipo(txt);
    std::string t = txt.substr(0,tam_t);
    txt.erase(0,tam_t);

    //return tipo(t) && funcaoretorno(txt);
    std::cout << t << "\n\n=============\n\n" << txt << "\n\n=============\n\n";
    return true
  }
  else {
    // Pega o identificador.
    int i = 0;
    std::locale loc;
    if (!std::isalpha(txt.begin(),loc)) {
      return false;
    }

    int tam_i = tam_id(txt)
    std::string letras = txt.substr(0, tam_i);
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
    if (tam_f == 0) {
      //return letra(letras) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2);
      std::cout << letras << "\n\n=============\n\n" << parametros << "\n\n=============\n\n" << txt.substr(1, tam_f-2) << "\n\n=============\n\n";
      return true;
    }
    else {
      //return letra(letras) && listadeParametros(parametros) && listadeComandos_(txt.substr(1, tam_f-2) && listadeFuncoes(txt.substr(tam_f));
      std::cout << letras << "\n\n=============\n\n" << parametros << "\n\n=============\n\n" << txt.substr(1, tam_f-2) << "\n\n=============\n\n" << txt.substr(tam_f) << "\n\n=============\n\n";
      return true && listadeFuncoes(txt.substr(tam_f));
    }
  }
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
