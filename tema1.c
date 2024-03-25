#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    void *f;
    char arg;
} Command_File_Type;

typedef struct queue_cell
{
    struct queue_cell *next;
    Command_File_Type *command;
} QueueCell;

typedef struct queue
{
    QueueCell *first;
    QueueCell *last;
} *QueueType;

typedef struct cell
{
    char info;
    struct cell *prev, *next;
} CellType;

typedef struct list
{
    CellType *sentinel;
    CellType *current;
} *List_Sentinel_Type;

typedef struct stack_cell
{
    struct stack_cell *next;
    CellType *info;
} StackCell, *StackType;

StackCell *add_cell_stack(CellType *info)
{
    // aceasta functie creeaza o noua celula in stiva, dupa
    // care ii asociem parametrul primit de functie si nodul
    // urmator drept null, iar in final returnam un pointer
    // la aceasta

    StackCell *nou = malloc(sizeof(StackCell));
    nou->info = info;
    nou->next = NULL;
    return nou;
}

void add_stack(StackType *s, CellType *info)
{
    // functia adauga un nou element in varful stivei s. initial
    // vom aloca o celula noua careia ii atribuim valoarea info
    // Daca alocarea a fost realizata cu succes vom adauga celula
    // nou creata in varful stivei.

    StackCell *nou = add_cell_stack(info);
    switch (nou != NULL)
    {
    case 1:
        nou->next = *s;
        *s = nou;
        break;
    default:
        break;
    }
}

void pop_stack(StackType *s)
{
    // functia extrage elementul din varful stivei. Vom initializa
    // variabila aux cu adresa nodului urmator, eliberam memoria
    // nodului curent si actualizam adresa pointer ului cu adresa
    // nodului urmator aux

    StackType aux = (*s)->next;
    free(*s);
    (*s) = aux;
}

int is_empty_stack(StackType s)
{

    // functia verifica daca stiva este goala si returneaza
    // prin intermediul operatorului ternar 1 daca este goala
    // si 0 in caz contrar

    return s ? 0 : 1;
}

void empty_stack(StackType *s)
{
    // goleste complet o stiva. cat timp aceasta nu este goala
    // vom elimina element cu element.

    while (!is_empty_stack(*s))
    {
        pop_stack(s);
    }
}

CellType *top_stack(StackType s)
{
    // returneza informatii despre nodul din varful stivei.
    // ea nu face nicio modificare asupra stivei

    return s->info;
}

QueueCell *add_cell_queue(void *f, char arg)
{
    // vom aloca initial o spatiu de memorie pentru o noua celula
    // dupa cacre vom aloca spatiu pentru o comanda a acesteia
    // si ii setam parametrii acesteia cu cei primiti ca argumente
    // si returnam un pointer la noua celula de coada

    QueueCell *nou = malloc(sizeof(*nou));
    nou->command = malloc(sizeof(*nou->command));
    nou->command->f = f;
    nou->command->arg = arg;
    return nou;
}

void add_queue(QueueType q, void *f, char arg)
{
    // adaug un nou element la sfarsitul cozii q. Alocam initial memorie
    // cu add_cell_queue. Daca coada nu este goala adaugam la sfarsitul
    // cozii. Daca este goala verificam daca este vida sau nu. Daca este vida
    // noua celula devine primul si ultimul element.

    QueueCell *nou = add_cell_queue(f, arg);
    switch (q->last != NULL)
    {
    case true:
        q->last->next = nou;
        break;
    case false:
        switch (q->first == NULL)
        {
        case true:
            q->first = nou;
            break;
        }
    }
    q->last = nou;
}

QueueType init_queue()
{
    // functia creeaza o noua coada si returneazaz un pointer
    // la aceasta dupa ce valorile first si last au fost initializate
    // cu null indicand ca aceasta este goala

    QueueType aux = malloc(sizeof(struct queue));
    aux->first = NULL;
    aux->last = NULL;
    return aux;
}

Command_File_Type *first_queue(QueueType q)
{

    // vom returna comanda primului element din coada primit ca
    // argument al functiei.

    return q->first->command;
}

bool is_empty_queue(QueueType q)
{

    // aceasta functie verifica daca coada primita ca argument
    // este goala sau nu. verificam astfel daca primul si ultimul
    // element sunt null, iar in caz afirmativ returnam true

    if (q->first == NULL && q->last == NULL)
        return true;

    return false;
}

void pop_queue(QueueType q)
{
    // prin acceast functie se elimina primul element din coada
    // astfel, conditia if va verifica daca exista un singur
    // element in coada, iar in acest caz se va elibera memoria,
    // iar pointer la primul si ultimul element vor deveni nuli.
    // in caz contrar, primul element este eliminat si vom indica
    // catre urmatorul element retinut in variabila primul_element

    if (q->first == q->last)
    {
        free(q->first->command);
        free(q->first);
        q->first = NULL;
        q->last = NULL;
    }
    else
    {
        QueueCell *primul_element = q->first->next;
        free(q->first->command);
        free(q->first);
        q->first = primul_element;
    }
}

void print_list_to_file(List_Sentinel_Type L, FILE *out)
{
    // aceasta fuctie scrie in fisier elementele din
    // lista cu santinela. prin folosirea unui switch
    // in interiorul while ului care parcurge lista
    // vom afisa astfel pe rand toate elementele in cazul
    // default, iar in cazul in care ne aflam la elementul
    // curent atunci folosim afisarea "|x|"

    CellType *p = L->sentinel->next;
    while (p != NULL)
    {
        switch (L->current != p)
        {
        case 0:
            fprintf(out, "|%c|", p->info);
            break;
        default:
            fprintf(out, "%c", p->info);
        }
        p = p->next;
    }
    fprintf(out, "\n");
}

CellType *allocate_cell(char c)
{
    // aceasta functie aloca memorie pentru o celula aux
    // si ii atribuie parametrul primit ca parametru al
    // functiei

    CellType *aux = (CellType *)malloc(sizeof(CellType));
    aux->info = c;
    aux->prev = aux->next = NULL;
    return aux;
}

void destroy_queue(QueueType q)
{
    // eliberez memoria cozii

    free(q);
}

void destroy_list(List_Sentinel_Type *listx)
{
    // functia primeste un pointer la lista si dezaloca
    // pe rand memoria pentru toate celulele din lista
    // in interiorul buclei, apoi elibereaza memoria
    // pentru santinela dupa care pentru lista in sine

    CellType *p = (*listx)->sentinel->next, *aux;
    do
    {
        aux = p;
        p = p->next;
        free(aux);
    } while (p != NULL);

    free((*listx)->sentinel);
    free(*listx);
}

List_Sentinel_Type init_list()
{
    // aceasta functie creeaza o lista vida si returneaza un pointer
    // la structura definita drept tip al functiei. Astfel, vom
    // initializa o celula cu santinela, o celula cu valoarea "#"
    // si returnam pointer la aceasta lista. Santinela are valoare
    // nedefinita. 0 mai precis in acest caz, dar este utila pentru
    // a evita probleme lucrului cu memoria la capetele listei.

    List_Sentinel_Type initl = (List_Sentinel_Type)malloc(sizeof(struct list));
    CellType *sentinel = allocate_cell(0);
    initl->sentinel = sentinel;
    CellType *first = allocate_cell('#');
    initl->sentinel->next = first;
    first->prev = sentinel;
    initl->current = first;
    return initl;
}

bool move_left_char(List_Sentinel_Type band, char c)
{
    // functia realizeaza cautarea dupa caracterul c in
    // stanga pozitiei cursorului. astfel ne vom muta repetat
    // la stanga in bucla, iar daca s a gasit vom returna adevarat
    // in caz contrar la finalul functiei vom fals daca dupa intreaga
    // cautare pana la santinela nu a fost gasit caracterul dat ca
    // parametru. In cazul in care s a gasit primul caracter vom muta
    // cursorul la pozitia acestuia

    CellType *aux = band->current;
    do
    {
        if (aux->info != c)
        {
            aux = aux->prev;
        }
        else
        {
            band->current = aux;
            return true;
        }
    } while (aux != band->sentinel);

    return false;
}

bool move_right_char(List_Sentinel_Type band, char c)
{
    // functia aceasta efectueaza o cautare a caracterului c
    // oferit ca parametru la dreapta de pozitia curenta.
    // Astfel, in fiecare iteratie a buclei se verifica daca
    // caracterul cautat nu este cel curent. Cand acesta a fost
    // gasit vom returna adevarat si actualizam pozitia curenta
    // a cursorului. In cazul in care s a ajuns la finalul listei
    // si nu s a gait caracterul cautat vom insera pe ultima pozitie
    // caracerul "#" si actulizam poziztia curenta la aceasta celula.

    CellType *aux = band->current, *prev;
    do
    {
        if (aux->info != c)
        {
            prev = aux;
            aux = aux->next;
        }
        else
        {
            band->current = aux;
            return true;
        }
    } while (aux != NULL);
    CellType *celula_noua = allocate_cell('#');
    prev->next = celula_noua;
    celula_noua->prev = prev;
    band->current = celula_noua;
    return true;
}

bool write(List_Sentinel_Type band, char c)
{
    // functia aceasta scrie caracterul c primit drept
    // parametru in celula curenta. Vom verifica initial
    // daca pe pozitia curenta se afla ceva, iar in caz
    // afirmativ vom realiza scrierea. La final verificam
    // daca scrierea a reusit.

    if (band->current == NULL)
    {
        return false;
    }
    band->current->info = c;
    if (band->current->info == c)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void insert_left(List_Sentinel_Type band, char c)
{
    // aceasta functie va insera elementul primit ca parametru
    // in stanga valorii curente a listei. ii vom atribui celulei
    // nou create campurile prev si next dupa care mutam pointer ul
    // curent pentru a arata la celula nou creata

    CellType *celula_noua = allocate_cell(c);
    celula_noua->prev = band->current->prev;
    celula_noua->next = band->current;
    band->current->prev->next = celula_noua;
    band->current->prev = celula_noua;
    band->current = celula_noua;
}

void insert_right(List_Sentinel_Type band, char c)
{
    // aceasta functie va insera elementul primit ca parametru
    // in dreapta valorii curente a listei. la fel ca in functia
    // precedeta vom atribui campurile next si pref dupa cae
    // mutam pointerul pentru a arata la celula nou creata.

    CellType *celula_noua = allocate_cell(c);
    celula_noua->prev = band->current;
    celula_noua->next = band->current->next;
    band->current->next = celula_noua;
    band->current = celula_noua;
}

bool move_left(List_Sentinel_Type band)
{
    // functia move_left verifica daca nodul de inantea
    // nodului santinela este null, iar in acest caz vom
    // returna fals, in caz contrar mutam cusorul la stanga
    // si returnam adevarat

    if (band->current->prev->prev == NULL)
    {
        return false;
    }
    band->current = band->current->prev;
    return true;
}

bool move_right(List_Sentinel_Type band)
{
    // aceasta functie muta cursorul la urmatoarea pozitie
    // la dreapta daca aceaasta exista. Initial verific
    // daca exista, iar in caz afirmativ se muta cursorul
    // altfel vom aloca o noua celula la dreapta dupa care
    // vom realiza mutarea.

    if (band->current->next != NULL)
    {
        band->current = band->current->next;
        return true;
    }
    band->current->next = allocate_cell('#');
    band->current->next->prev = band->current;
    band->current = band->current->next;
    return true;
}

void process_command(List_Sentinel_Type band, StackType *undo, StackType *redo,
    QueueType queue, char *comanda, char argum, FILE *out_file, FILE *in_file)
{
    // functia primeste toti parametrii de care are nevoie pentru
    // a verifica ce comanda primeste drept intrare in fisierul text
    // iar in functie de aceasta decizia va alege ce operatii sa efectueze
    // benzii. Am incercat initial sa implementez un switch cu toate comenzile
    // dar nu am reusit sa il fac sa functioneze. L am lasat in aceasta varianta
    // in care doar imparte dupa prima litera pentru o mai buna lizibilitate. de
    // altfel inutila. Toate comenzile vin insotite de apelurile functiilor ce
    // modifica lista/coada/stivele, iar cea de execute se ocupa si cu tratarea
    // erorilor.

    switch (comanda[0])
    {
    case 'M':
        if (!strcmp(comanda, "MOVE_LEFT"))
        {
            add_queue(queue, move_left, 0);
        }
        else if (!strcmp(comanda, "MOVE_RIGHT"))
        {
            add_queue(queue, move_right, 0);
        }
        else if (!strcmp(comanda, "MOVE_LEFT_CHAR"))
        {
            fscanf(in_file, "%c%c", &argum, &argum);
            add_queue(queue, move_left_char, argum);
        }
        else if (!strcmp(comanda, "MOVE_RIGHT_CHAR"))
        {
            fscanf(in_file, "%c%c", &argum, &argum);
            add_queue(queue, move_right_char, argum);
        }
        break;
    case 'W':
        if (!strcmp(comanda, "WRITE"))
        {
            fscanf(in_file, "%c%c", &argum, &argum);
            add_queue(queue, write, argum);
            empty_stack(undo);
        }
        break;
    case 'I':
        if (!strcmp(comanda, "INSERT_LEFT"))
        {
            fscanf(in_file, "%c%c", &argum, &argum);
            add_queue(queue, insert_left, argum);
        }
        else if (!strcmp(comanda, "INSERT_RIGHT"))
        {
            fscanf(in_file, "%c%c", &argum, &argum);
            add_queue(queue, insert_right, argum);
        }
        break;
    case 'S':
        if (!strcmp(comanda, "SHOW_CURRENT"))
        {
            fprintf(out_file, "%c\n", band->current->info);
        }
        else if (!strcmp(comanda, "SHOW"))
        {
            print_list_to_file(band, out_file);
        }
        break;
    case 'U':
        if (!strcmp(comanda, "UNDO"))
        {
            add_stack(redo, band->current);
            band->current = top_stack(*undo);
            pop_stack(undo);
        }
        break;
    case 'R':
        if (!strcmp(comanda, "REDO"))
        {
            add_stack(undo, band->current);
            band->current = top_stack(*redo);
            pop_stack(redo);
        }
        break;
    case 'E':
        if (!strcmp(comanda, "EXECUTE"))
        {
            if (!is_empty_queue(queue))
            {
                CellType *initialPosition = band->current;
                int (*command)() = (int (*)())(first_queue(queue)->f);
                char arg = first_queue(queue)->arg;
                int errorCode = 0;
                if (arg)
                {
                    errorCode = command(band, arg);
                }
                else
                {
                    errorCode = command(band);
                }

                if (errorCode == -1)
                {
                    if ((band->current == 0) && strcmp(first_queue(queue)->f, "MOVE_LEFT") != 0)
                        fprintf(out_file, "ERROR\n");
                }
                pop_queue(queue);
                if (initialPosition != band->current)
                {
                    add_stack(undo, initialPosition);
                }
            }
        }
        break;
    default:
        break;
    }
}

int main()
{
    // functia main se ocupa de initializaile fisierelor, stivelor,
    // listei cu santinela, cozii si de eliberarea memoriei la final.
    // Totodata, pentru fiecare citire din fisier vom apela funcita
    // process_command cu parametrii potriviti unde vom verifica
    // ce functie a fost citita si in functie de asta vom decide ce
    // operatii sa realizam cu banda noastra.

    List_Sentinel_Type band = init_list();
    StackType undo = NULL;
    StackType redo = NULL;
    QueueType queue = init_queue();
    FILE *out_file = fopen("tema1.out", "w");
    FILE *in_file = fopen("tema1.in", "r");
    int n = 0, i;
    fscanf(in_file, "%d", &n);

    for (i = 0; i < n; i++)
    {
        char comanda[30], argum;
        strcpy(comanda, "");
        argum = '\0';
        fscanf(in_file, "%s", comanda);
        process_command(band, &undo, &redo, queue, comanda, argum, out_file, in_file);
    }
    fclose(in_file);
    fclose(out_file);
    destroy_queue(queue);
    destroy_list(&band);
    empty_stack(&undo);
    empty_stack(&redo);
    return 0;
}
