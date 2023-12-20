#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <fstream>
#include <time.h>
#include <sstream>

using namespace std;

struct node {
    node *next;
    node *prev;
    string *data;
    int identifier;
};

struct tab {
    int number_of_columns;
    int number_of_rows;
    node *head;
    node *tail;
};

struct table {
    tab *sections;
    int number_of_sections;
};

void length(tab &sheet); //return number of nodes in tab
void print(tab *sheet); //print the values in tab
void push(tab *sheet, string *new_data); //push to front of tab
void clear(tab *sheet); //remove all nodes from tab
void clear(tab **sheet); //removes all nodes from a complete sheet
void sort_tabs(ofstream &output, tab *sheet, const string &save_location); //Split the tab into sections based on the sections array
void convert_tabs(ofstream &output, table *sheet, const string &save_location); //Convert the tab to an html page based on section identifier
void search_tabs(table *sheet); //Searches through a table pulling out nodes that have strings that match the search term
void get_new_filename(string &filename);
void extension_parse(string &filename);
void argument_parse(int argc, char *argv[], string &filename);
void create_save_location(const string &filename, string &save_location);
void conversion(const string &load_location, const string &save_location);
void read_file(ofstream &output, tab *sheet, const string &filename, const string &save_location);
void tab_compile(ofstream &output,const string &save_location, string &operation, string &header, int &number_of_columns);

/***********************************************************************************************************
 Function: length
 Description: Iterates through the list to determine the actual size.
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: The size/length of the given sheet is set.
 ************************************************************************************************************/

void length(tab &sheet){
    int size = 0;

    //Begin at the back of the list
    node* temp = sheet.tail->next;

    //Loop until the last node is reached
    while(temp->next != NULL){
        //Incrememt size
        size++;
        //Move to the next node
        temp = temp->next;
    }

    //Set the size of the given sheet to the found size
    sheet.number_of_rows = size;
}

/***********************************************************************************************************
 Function: print
 Description: Prints the data contained in each node for a tab node.
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: NA
 ************************************************************************************************************/

void print(tab *sheet){
    node* temp;

    //Check to make sure the given tab has data.
    if(sheet->tail == NULL && sheet->head == NULL){
        cout << "                                                  The tab is empty!" << endl;
        return;
    }

    //Start at the front of the tab
    temp = sheet->head->prev;

    //Iterate while within the bounds of the tab
    while(temp->prev != NULL){
        //Iterate through the current nodes data printing each cell individually
        for(int i = 0; i < sheet->number_of_columns; i++){
            //Signify seperate cells and the the final cell.
            if(i < (sheet->number_of_columns - 1)){
                cout << temp->data[i] << ", ";
            } else {
                cout << temp->data[i] << "." << endl;
            }
        }

        //Move to the next node.
        temp = temp->prev;
    }

}

/***********************************************************************************************************
 Function: clear(tab *sheet)
 Description: Clears the data and nodes contained in base tab
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: The data that has been allocated for the tab has been successfully cleared.
 ************************************************************************************************************/

void clear(tab *sheet){
    node* delete_next; node* deletion_node;

    if(sheet->tail == NULL && sheet->head == NULL){
        //cout << "                           This tab is empty!" << endl;
        return;
    }

    deletion_node =  sheet->head->prev;

    while(deletion_node->prev != NULL){
        delete_next = deletion_node->prev;

        delete [] deletion_node->data;
        delete deletion_node;

        deletion_node = delete_next;
    }

    delete sheet->head;
    delete sheet->tail;

}

/***********************************************************************************************************
 Function: clear(table *sheet)
 Description: Clears the data and nodes inside of a split tab.
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: The data that has been allocated for the tab has been successfully cleared.
 ************************************************************************************************************/

void clear(table *sheet){
    node* delete_next; node* deletion_node;

    for(int i = 0; i < sheet->number_of_sections; i++){
        deletion_node =  sheet->sections[i].head->prev;

        if(sheet->sections[i].tail == NULL && sheet->sections[i].head == NULL){
            //cout << "                           This tab is empty!" << endl;
        } else {
            while(deletion_node->prev != NULL){
                delete_next = deletion_node->prev;

                delete [] deletion_node->data;
                delete deletion_node;

                deletion_node = delete_next;
            }
        }

        delete sheet->sections[i].head;
        delete sheet->sections[i].tail;

    }

    delete [] sheet->sections;

}

/***********************************************************************************************************
 Function: rollup
 Description: Determines the college of the award from the org code.
 Return: COLLEGE - The name of the college.
 Pre-Conditions: NA
 Post-Conditions: The college has been determined.
 ************************************************************************************************************/
 string rollup( string org_code ) {
     int org_number = 0;
     string college = "";

     try {
         org_number = stoi( org_code.substr( 0, 2 ) ); // Get the first to characters of the org code as a number
     } catch( ... ) {
         org_number = 99;
     }

     switch ( org_number ) {
         // case 10:
         //     college = "Enrollment Management";
         //     break;
         // case 11:
         //     college = "Academic Affairs";
         //     break;
         // case 12:
         //     college = "Information Services";
         //     break;
         // case 13:
         //     college = "Graduate School";
         //     break;
         // case 14:
         //     college = "Extension";
         //     break;
         // case 15:
         //     college = "Vice President for Research";
         //     break;
         // case 16:
         //     college = "Student Affairs";
         //     break;
         // case 17:
         //     college = "International Programs";
         //     break;
         // case 18:
         //     college = "Honors College";
         //     break;
         // case 19:
         //     college = "Cascades Campus";
         //     break;
         case 21:
             college = "College of Agricultural Sciences";
             break;
         case 22:
             college = "College of Veterinary Medicine";
             break;
         case 23:
             college = "College of Forestry";
             break;
         case 24:
             college = "College of Liberal Arts";
             break;
         case 25:
             college = "College of Science";
             break;
         case 26:
             college = "College of Earth, Ocean, and Atmospheric Sciences";
             break;
         case 27:
             college = "College of Business";
             break;
         case 30:
             college = "College of Engineering";
             break;
         case 31:
             college = "College of Education";
             break;
         case 32:
             college = "College of Public Health and Human Sciences";
             break;
         case 33:
             college = "College of Pharmacy";
             break;
         // case 42:
         //     college = "Business Services";
         //     break;
         default:
            college = "Other";
            break;
     }

     return college;
 }

/***********************************************************************************************************
 Function: push
 Description: Initializes a tab and adds nodes to the tab from given data.
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: A tab has been initialized and the new node has been successfully added.
 ************************************************************************************************************/

void push(tab *sheet, string *new_data){
    node* new_node = new node; node* temp;

    for(int i = 0; i < sheet->number_of_columns; i++){
        if(new_data[i] == "" || new_data[i] == " " || new_data[i] == "N/A"){
            new_data[i] = "NA";
        }
        if ( i == sheet->number_of_columns - 1 ) {
            new_data[ i ] = rollup( new_data[ i ] );
        }
    }

    /* for(int i = 0; i < 8; i++) {
        std::cout << new_data[i];
        if (i==7) {
            std::cout << '\n';
        }
    } */


    if((int)new_data[0].at(0) > 96){ new_data[0].at(0) = new_data[0].at(0) - 32; }

    if(sheet->head == NULL && sheet->tail == NULL){
        sheet->head = new node;
        sheet->tail = new node;

        sheet->head->next = NULL;
        sheet->head->data = NULL;
        sheet->head->prev = new_node;

        new_node->data = new_data;

        if(new_node->data[7] == "Set-Up in Process"){
            new_node->identifier = 1;
        } else if (new_node->data[7] != "Set-Up in Process" && new_node->data[5] == "Outgoing Subaward/Contract"){
            new_node->identifier = 2;
        } else {
            new_node->identifier = 0;
        }

        new_node->next = sheet->head;
        new_node->prev = sheet->tail;

        sheet->tail->next = new_node;
        sheet->tail->data = NULL;
        sheet->tail->prev = NULL;

    } else {
        temp = sheet->head->prev;
        temp->next = new_node;

        new_node->data = new_data;


        if(new_node->data[7] == "Set-Up in Process" || new_node->data[7] == "IRB/IACUC Approval Requested"){
            new_node->identifier = 1;
        } else if (new_node->data[7] != "Set-Up in Process" && new_node->data[5] == "Outgoing Subaward/Contract"){
            new_node->identifier = 2;
        } else {
            new_node->identifier = 0;
        }

        new_node->prev = temp;
        new_node->next = sheet->tail;

        sheet->head->prev = new_node;
    }

}

/***********************************************************************************************************
 Function: sort_tabs
 Description: Sorts the initial tab into seperate sections sorted in alphabetcal order
 Return: NA
 Pre-Conditions: save_location is a valid location, the sheet has been initialized, and output can be used properly
 Post-Conditions: The tab has been broken down in the appropiate manner.
 ************************************************************************************************************/

void sort_tabs(ofstream &output, tab *sheet, const string &save_location){
    int loc, secs = 3, number_of_rows[secs];
    table *section_table = NULL;
    node *insert_node = NULL, *next_node = NULL;
    node *node_to_check = NULL, *next_check = NULL;

    //Check to make sure there are elements in the sheet
    if(sheet->tail == NULL){
        //cout << "                            The tab is empty!" << endl;
        return;
    }

    section_table = new table;
    section_table->sections = new tab[secs];
    section_table->number_of_sections = secs;
    fill_n(number_of_rows, secs, 0);

    for(int i = 0; i < secs; i++){
        section_table->sections[i].tail = NULL;
        section_table->sections[i].head = NULL;
        section_table->sections[i].number_of_columns = sheet->number_of_columns;
    }

    //Get the initial node
    insert_node = sheet->tail->next;

    while(insert_node->next != NULL){
        //Save the next node in the list
        next_node = insert_node->next;

        //Save the section location of the current node
        loc = insert_node->identifier;
        next_node->prev = sheet->tail; sheet->tail->next = next_node;

        //Check to see if the current tab is empty
        //If empty; initialize the specific tab section
        //If it is full iterate through the sorted section and insert the new node
        if(insert_node->data == NULL){ break; }
        if(section_table->sections[loc].head == NULL && section_table->sections[loc].tail == NULL){
            section_table->sections[loc].head = new node;
            section_table->sections[loc].tail = new node;

            section_table->sections[loc].head->next = NULL;
            section_table->sections[loc].head->data = NULL;
            section_table->sections[loc].head->prev = insert_node;

            insert_node->next = section_table->sections[loc].head;
            insert_node->prev = section_table->sections[loc].tail;

            section_table->sections[loc].tail->next = insert_node;
            section_table->sections[loc].tail->data = NULL;
            section_table->sections[loc].tail->prev = NULL;
        } else {
            node_to_check = section_table->sections[loc].tail->next;
            //Continue while the next node exists break when a node has been inserted
            while(node_to_check->next != NULL){
                next_check = node_to_check->next;
                //Compare the insert node to the current sorted node
                //If it is less than the current node place before the current sorted node
                //If it is greater than (or equal to) and it is at the last place
                //insert at the last location in the tab.
                //If it does not satisfy either condition; continue to the next node.
                if(insert_node->data[0] > node_to_check->data[0]){
                    //Insert the node infront the node behind of node_to_check
                    node_to_check->prev->next = insert_node;

                    //Finish the insertion by having node_to_check and insert_node point to each other
                    insert_node->prev = node_to_check->prev;
                    insert_node->next = node_to_check;
                    node_to_check->prev = insert_node;

                    break;
                } else if(((insert_node->data[0] < node_to_check->data[0]) ||
                            insert_node->data[0] == node_to_check->data[0])
                            && node_to_check->next->next == NULL){
                    //Insert the node behind the node infront of node_to_check
                    node_to_check->next->prev = insert_node;

                    //Finish the insertion by having node_to_check and insert_node point to each other
                    insert_node->next = node_to_check->next;
                    insert_node->prev = node_to_check;
                    node_to_check->next = insert_node;

                    break;
                } else {
                    //Continue to the next node in the sorted tab
                    node_to_check = next_check;
                }
            }
        }
        number_of_rows[loc] += 1;
        insert_node = next_node;
    }

    for(int i = 0; i < secs; i++){ length(section_table->sections[i]); }

    convert_tabs(output, section_table, save_location);
    //search_tabs(section_table);


    clear(section_table);
    delete sheet->head;
    sheet->tail = NULL; sheet->head = NULL;
    delete insert_node;
    delete section_table;
}

/***********************************************************************************************************
 Function: convert_tabs
 Description: Iterates through a table and converts each section tab into a HTML table
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: The table has been converted into valid HTML markup
 ************************************************************************************************************/

void convert_tabs(ofstream &output, table *sheet, const string &save_location){
    ostringstream element;
    node* convert_next; node* conversion_node;
    int secs = sheet->number_of_sections, cols = 0;
    string row = "", cell = "", operation = "", header = "", jump = "";

    for (int sec = 0; sec < secs; sec++){
        if(sec == 0){ header = "Awards in Process"; }
        else if(sec == 1){ header = "Setup in Process"; }
        else { header = "Outgoing Subawards and Contracts"; }
        operation = "start"; cols = sheet->sections[sec].number_of_columns;

        output.open(save_location.c_str(), ios::app);
        if(sec == 1){ jump = "\n<p>\n\t<a name=\"SP\"></a>\n</p>\n"; }
        if(sec == 2){ jump = "\n<p>\n\t<a name=\"OS\"></a>\n</p>\n"; }
        output << jump;
        output.close();

        tab_compile(output, save_location, operation, header, cols);

        conversion_node = sheet->sections[sec].head->prev;

        if(sheet->sections[sec].tail == NULL && sheet->sections[sec].head == NULL){
            //cout << "                           This tab is empty!" << endl;
        } else {
            while(conversion_node->prev != NULL){
                output.open(save_location.c_str(), ios::app);

                convert_next = conversion_node->prev;
                row = "\t\t<tr align=\"center\" valign=\"middle\" data-department=\"" + conversion_node->data[ cols - 1 ] + "\">\n"; output << row;

                for(int col = 0; col < cols - 1; col++){
                    element << "\t\t\t<td colspan=\"1\" ";

                    if(col == 0){ element << "width=\"15%\""; }
                    else if (col == 1){ element << "width=\"20%\""; }
                    else if (col == 2){ element << "width=\"7.5%\""; }
                    else if (col == 3){ element << "width=\"7.5%\""; }
                    else if (col == 4){ element << "width=\"10%\""; }
                    else if (col == 5){ element << "width=\"10%\""; }
                    else if (col == 6){ element << "width=\"15%\""; }
                    else if (col == 7){ element << "width=\"15%\""; }
                    else { cout << "error"; }

                    element <<" align=\"center\" valign=\"middle\">\n\t\t\t\t<p>";
                    element << conversion_node->data[col];
                    element << "</p>\n\t\t\t</td>\n";

                    cell = element.str();

                    output << cell;

                    cell = "";
                    element.str("");
                    element.clear();
                }

                row = "\t\t</tr>\n\n"; output << row;
                conversion_node = convert_next;

                output.close();
            }

        }

        operation = "end";
        tab_compile(output, save_location, operation, header, cols);

    }
}

/***********************************************************************************************************
 Function: search_tabs
 Description: Iterates through a table and picks out nodes that match the given search term.
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: The correct nodes have been identified and picked out.
 ************************************************************************************************************/

 void search_tabs(table *sheet){
     node* compare_node; node* compare_next;
     int count = 0, secs = sheet->number_of_sections;
     string comparison_string = "", equator_string = "";

     cout << endl << "Enter the search term: ";
     cin >> equator_string;
     cout << endl;

     for(int sec = 0; sec < secs; sec++){
         compare_node =  sheet->sections[sec].tail->next;

         if(sheet->sections[sec].tail == NULL && sheet->sections[sec].head == NULL){
         } else {
             while(compare_node->next != NULL){
                 compare_next = compare_node->next;

                 for(int c = 0; c < sheet->sections[sec].number_of_columns; c++){
                     comparison_string = compare_node->data[c];
                     if(comparison_string == equator_string){
                         count++;
                     }

                 }

                 compare_node = compare_next;
             }
         }
     }

     cout << "                                Instance Count: "<< count << endl;

}

/***********************************************************************************************************
 Function: conversion
 Description: Main driver for the conversion process
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: NA
 ************************************************************************************************************/

void conversion(const string &load_location, const string &save_location) {
    double diff;
    time_t begin, end;
    string operation;

    tab *sheet = new tab;
    sheet->head = NULL; sheet->tail = NULL;

    begin = clock();

    ofstream output(save_location.c_str());
    output.close();

    read_file(output, sheet, load_location, save_location);
    sort_tabs(output, sheet, save_location);

    clear(sheet);
    delete sheet;

    end = clock();
    diff = (double)(end - begin) / CLOCKS_PER_SEC;

    cout<<"                           Process Time: "<<diff<<" seconds."<<endl;

}

/***********************************************************************************************************
 Function: tab_compile
 Description:
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: NA
 ************************************************************************************************************/

void tab_compile(ofstream &output, const string &save_location, string &operation, string &header, int &number_of_columns){
    string element = "";
    ostringstream head, tail;
    output.open(save_location.c_str(), ios::app);

    string tableID = "", headerID = "", footerID = "";

    if(header == "Awards in Process"){ tableID = "awards"; headerID = "awardsHead"; footerID = "awardsFoot"; }
    else if (header == "Setup in Process"){ tableID = "setup"; headerID = "setupHead"; footerID = "setupFoot"; }
    else { tableID = "outgoing"; headerID = "outgoingHead"; footerID = "outgoingFoot"; }

    if(operation == "start"){
        head << "<table id=\""<<tableID<<"\" style=\"width: 100%; top: -10px\" border=\"1\" cellspacing=\"0\" cellpadding=\"0\">\n"
        "\t<tbody>\n"
        "\t\t<tr id=\""<<headerID<<"\" style=\"background-color: #373737;\" align=\"center\" valign=\"middle\">\n"
        "\t\t\t<td style=\"width: 41%;\" colspan=\"" << number_of_columns << "\" align=\"center\" valign=\"middle\">\n"
        "\t\t\t\t<h4 style=\"color: #f5f2ed;\">"<< header <<"</h4>\n"
        "\t\t\t</td>\n"
        "\t\t</tr>\n";

        element = head.str();

    } else {
        tail << "\t\t<tr id=\""<<footerID<<"\" style=\"background-color: #373737;\" align=\"center\" valign=\"middle\">\n"
        "\t\t\t<td colspan=\"" << number_of_columns << "\" align=\"center\" valign=\"middle\">\n"
        "\t\t\t\t<p style=\"font-size: 13px;\"><a href=\"#Top\" style=\"color: #f5f2ed;\" style=\"color: #f5f2ed;\">Back to top</a></p>\n"
        "\t\t\t</td>\n"
        "\t\t</tr>\n\t</tbody>\n</table>";

        element = tail.str();

    }

    output << element;

    output.close();
}

/***********************************************************************************************************
 Function:
 Description:
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: NA
 ************************************************************************************************************/

void read_file(ofstream &output, tab *sheet, const string &filename , const string &save_location){
    char c;
    bool name = false, broken_line = false;
    unsigned long int length;
    int cell, run = 0, cells_parsed = 1;
    string *row_data, *temp_row;
    string line, content, operation, stored_line;
    ifstream input;

    input.open( filename.c_str() );

    if (input.fail() ) {
        cout<<"                        The file specified failed to import."<<endl;
    } else {
        cout<<"                        The file was successfully imported."<<endl;
    }


    while( getline( input, line ) ){

        cout << broken_line << " -> ";

        if ( broken_line ) {
            string temp = line;
            line.clear();
            line.append( stored_line );
            line.append( temp );
            broken_line = false;
        }

        cout << line << endl;

        length = line.size();
        // TODO: FIX dynamic sizing. i.e. 9 below needs to be sized for any number of columns. Random sampling to find true count?
        row_data = new string[ 9 ];
        fill_n( row_data, cells_parsed, "" );

        run++;
        cell = 1;
        cells_parsed = 1;
        name = false;

        for( int i = 0; i < length - 1; i++ ){
            c = line.at( i );

            if( ( int ) c == 34 && !name ){
                name = true;
            } else if( ( int ) c == 34 ){
                name = false;
            } else if ( c == ',' && !name ) {
                if( run == 1 ) {
                    if( cells_parsed > 1 ) {
                        temp_row = new string[ cells_parsed ];

                        for( int r = 0; r < ( cells_parsed - 1 ); r++ ){ temp_row[ r ] = row_data[ r ]; }

                        temp_row[ cells_parsed - 1 ] = content;

                        delete [] row_data;
                        row_data = temp_row;

                    } else { row_data[ cell - 1 ] = content; }

                } else { row_data[ cell - 1 ] = content; }

                cell += 1; content.clear(); cells_parsed += 1;

            } else { content += c; }

        }

        if( run == 1 ) {
            sheet->number_of_columns = cells_parsed;

            if( cells_parsed > 1 ) {
                temp_row = new string[ cells_parsed ];

                for( int r = 0; r < ( cells_parsed - 1 ); r++ ){ temp_row[ r ] = row_data[ r ]; }

                temp_row[ cells_parsed - 1 ] = content;

                delete [] row_data;
                row_data = temp_row;

            } else { row_data[ cell - 1 ] = content; }

        } else { row_data[ cell - 1 ] = content; }

        if ( cells_parsed < sheet->number_of_columns ) {
            broken_line = true;
            stored_line = line;
            stored_line.replace( stored_line.begin() + stored_line.length() - 1, stored_line.end(), " " );
        } else {
            push( sheet, row_data );
        }

        content.clear();

    }

    input.close();


}

/***********************************************************************************************************
 Function:
 Description:
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: NA
 ************************************************************************************************************/

void get_new_filename(string &filename){
    cout<<"Please enter a filename ending in .csv\n(Must be located in the current directory): ";
    cin>>filename;
    cout<<endl;

    extension_parse(filename);
}

/***********************************************************************************************************
 Function:
 Description:
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: NA
 ************************************************************************************************************/

void extension_parse(string &filename){
    int length = 0, j = 1;
    char extension[4], correct_ext[4] = {'.', 'c', 's', 'v'};

    fill_n(extension, 4, ' ');

    length = (int)filename.size();
    extension[0] = filename.at(length - 4);

    //Checks to make sure the extension is 3 characters long
    while (extension[0] != '.'){
        cout<<"The filename you have entered is incorrect!"<<endl<<"Please enter a name ending in .csv: ";
        cin>>filename;
        cout<<endl;

        length = (int)filename.size();
        extension[0] = filename.at(length - 4);
    }

    //Adds the last three characters to an array to make sure the spell txt
    for(int i = (length - 3); i < length; i++){
        extension[j] = filename.at(i);
        j++;
    }

    for(int i = 0; i < 4; i++){
        if(extension[i] != correct_ext[i]){
            get_new_filename(filename);
            return;
        }
    }
}

/***********************************************************************************************************
 Function:
 Description:
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: NA
 ************************************************************************************************************/

void argument_parse(int argc, char *argv[], string &filename){
    if(argc > 3){ cout<<"You have entered to many arguements!"<<endl; exit(0);}
    if(argc < 3){ cout<<endl; get_new_filename(filename); return;}

    if(!(argv[1][0] == '-' && argv[1][1] == 'f')){
        cout<<"You have entered the wrong sequence of aguements!"<<endl
        <<"::::  -f = filename   ::::"<<endl;
        exit(0);
    }

    for(int i  = 0; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'f' && argv[i][2] == '\0'){
            filename = argv[i+1];
        }
    }

    extension_parse(filename);

}

/***********************************************************************************************************
 Function:
 Description:
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: NA
 ************************************************************************************************************/

void create_save_location(const string &filename, string &save_location) {

    size_t deli_pos = filename.find_last_of( "." );
    save_location = filename.substr( 0, deli_pos );
    save_location.append( ".html" );

}

/***********************************************************************************************************
 Function:
 Description:
 Return: NA
 Pre-Conditions: NA
 Post-Conditions: NA
 ************************************************************************************************************/

int main(int argc, char *argv[]) {
    double diff;
    time_t begin, end;
    string load_location, save_location, operation;

    argument_parse(argc, argv, load_location);
    create_save_location(load_location, save_location);

    cout<<endl<<endl<<endl;
    cout<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
    cout<<":::::::::::                                                          :::::::::::"<<endl;
    cout<<":::::::::::                   CSV to HTML Converter                  :::::::::::"<<endl;
    cout<<":::::::::::                                                          :::::::::::"<<endl;

    conversion(load_location, save_location);

    cout<<endl;
    cout<<":::::::::::                                                          :::::::::::"<<endl;
    cout<<":::::::::::                     Conversion Completed                 :::::::::::"<<endl;
    cout<<":::::::::::                                                          :::::::::::"<<endl;
    cout<<"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"<<endl;
    cout<<endl<<endl<<endl;

    system("pause");

    return 0;
}
