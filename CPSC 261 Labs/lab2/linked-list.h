/*
 * Declarations.
 */
struct s_node
{
    long value;
    struct s_node *next;
};

/*
 * Function prototypes for the functions we provide.
 */
extern struct s_node *create_list();
extern void print(struct s_node *head);
extern void insert_front(struct s_node *head, long value);

/*
 * Function prototypes for the functions you need to write.
 */
extern void print_with_positions(struct s_node *head);
extern long get_element_at(struct s_node *head, int position);
extern void free_list(struct s_node *head);
extern int insert_at(struct s_node *head, int position, long value);
extern int insert_list_at(struct s_node *head, int position, struct s_node *other_head);
extern struct s_node *extract_sublist(struct s_node *head, int position, int nb_of_elements);


