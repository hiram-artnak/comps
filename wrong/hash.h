


typedef enum cetegory_type {FUNCTION_TYPE, ID_TYPE, LITERAL_TYPE} category_type; // Can be a function, literal or an id

typedef enum data_type {INT_TYPE, FLOAT_TYPE, BOOL_TYPE} data_type;

typedef TableData
{
    int localization; // line where the lexeme appears in the program
    category_type category; 
    data_type type;
    
}TableData;

typedef TableCell
{
 TableData entry;
 int id; // 
} TableCell;


