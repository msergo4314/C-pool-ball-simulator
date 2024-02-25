#include "phylib.h"
// Functions to allocate memory for new objects
phylib_object *phylib_new_still_ball(unsigned char number, phylib_coord *pos) {
    if (pos == NULL) {
        printf("ERROR NO COORDINATES FOR NEW STILL BALL\n");
        return NULL;
    }
    phylib_object *new_obj = (phylib_object*)malloc(sizeof(phylib_object));
    phylib_coord temp_pos = {pos->x, pos->y};
    if (new_obj != NULL) {
        new_obj->type = PHYLIB_STILL_BALL;
        new_obj->obj.still_ball.number = number;
        new_obj->obj.still_ball.pos = temp_pos;
    }
    else
    {
        printf("NEW STILL BALL UNALLOCATED\n");
    }
    return new_obj;
}

phylib_object *phylib_new_rolling_ball(unsigned char number, phylib_coord *pos, phylib_coord *vel, phylib_coord *acc) {
    if (pos == NULL || vel == NULL || acc == NULL) {
        printf("ERROR POS, VEL OR ACC NOT FOUND FOR NEW ROLLING BALL\n");
        return NULL;
    }
    phylib_object *new_obj = (phylib_object *)malloc(sizeof(phylib_object));
    phylib_coord temp_pos = {pos->x, pos->y};
    phylib_coord temp_vel = {vel->x, vel->y};
    phylib_coord temp_acc = {acc->x, acc->y};
    if (new_obj != NULL) {
        new_obj->type = PHYLIB_ROLLING_BALL;
        new_obj->obj.rolling_ball.number = number;
        new_obj->obj.rolling_ball.pos = temp_pos;
        new_obj->obj.rolling_ball.vel = temp_vel;
        new_obj->obj.rolling_ball.acc = temp_acc;
    }
    else{
        printf("NEW ROLLING BALL UNALLOCATED\n");
    }
    return new_obj;
}

phylib_object *phylib_new_hole(phylib_coord *pos) {
    if (pos == NULL) {
        printf("ERROR NO POS FOR NEW HOLE\n");
        return NULL;
    }
    phylib_object *new_obj = (phylib_object *)malloc(sizeof(phylib_object));
    phylib_coord temp_pos = {pos->x, pos->y};
    if (new_obj != NULL) {
        new_obj->type = PHYLIB_HOLE;
        new_obj->obj.hole.pos = temp_pos;
    }
    else 
    {
        printf("ERROR MEMORY NOT ALLOCATED FOR NEW HOLE\n");
    }
    return new_obj;
}
 
phylib_object *phylib_new_hcushion(double y) {
    phylib_object *new_obj = (phylib_object *)malloc(sizeof(phylib_object));
    if (new_obj != NULL) {
        new_obj->type = PHYLIB_HCUSHION;
        new_obj->obj.hcushion.y = y;
    }
    else{
        printf("ERROR NO MEMORY ALLOCATED FOR NEW HCUSION\n");
    }
    return new_obj;
}

phylib_object *phylib_new_vcushion(double x) {
    phylib_object *new_obj = (phylib_object *)malloc(sizeof(phylib_object));
    if (new_obj != NULL) {
        new_obj->type = PHYLIB_VCUSHION;
        new_obj->obj.vcushion.x = x;
    }
    else{
        printf("ERROR NO MEMORY ALLOCATED FOR NEW VCUSION\n");
    }
    return new_obj;
}

phylib_table *phylib_new_table(void) {
    phylib_table *new_table = (phylib_table *)malloc(sizeof(phylib_table));
    if (new_table != NULL) {
        new_table->time = 0.0;

        for (int i = 0; i < PHYLIB_MAX_OBJECTS; i++)
        {
            (new_table->object)[i] = NULL;
        }
        
        // Add cushions
        phylib_add_object(new_table, phylib_new_hcushion(0.0));
        phylib_add_object(new_table, phylib_new_hcushion(PHYLIB_TABLE_LENGTH));
        phylib_add_object(new_table, phylib_new_vcushion(0.0));
        phylib_add_object(new_table, phylib_new_vcushion(PHYLIB_TABLE_WIDTH));

        // Add holes
        phylib_add_object(new_table, phylib_new_hole(&(phylib_coord){0.0, 0.0}));
        phylib_add_object(new_table, phylib_new_hole(&(phylib_coord){0.0, PHYLIB_TABLE_LENGTH / 2.0}));
        phylib_add_object(new_table, phylib_new_hole(&(phylib_coord){0.0, PHYLIB_TABLE_LENGTH}));
        phylib_add_object(new_table, phylib_new_hole(&(phylib_coord){PHYLIB_TABLE_WIDTH, 0.0}));
        phylib_add_object(new_table, phylib_new_hole(&(phylib_coord){PHYLIB_TABLE_WIDTH, PHYLIB_TABLE_LENGTH / 2.0}));
        phylib_add_object(new_table, phylib_new_hole(&(phylib_coord){PHYLIB_TABLE_WIDTH, PHYLIB_TABLE_LENGTH}));
    }
    else{
        printf("ERROR NO MEMORY ALLOCATED FOR NEW TABLE\n");
    }
    return new_table;
}

// Functions to copy individual objects and table
void phylib_copy_object(phylib_object **dest, phylib_object **src) {

    phylib_object *memloc = (phylib_object*)malloc(sizeof(phylib_object));

    if (memloc == NULL)
    {
        printf("MEMLOC MEMORY ALLOCATION FAILED\n");
        return;
    }
    
    if (src == NULL || dest == NULL)
    {
        printf("SRC OR DEST ARE NULL\n");
        free(memloc);
        return;
    }

    if (*src == NULL )
    {
        *dest = NULL;
        free(memloc);
        return;
    }
    
    *dest = memloc;
    memcpy(*dest, *src, sizeof(phylib_object));
    return;
}

phylib_table *phylib_copy_table(phylib_table *table) {
    if (table == NULL) {
        printf("TABLE NULL FOR COPY TABLE\n");
        return NULL;
    }
    phylib_table *new_table = (phylib_table *)malloc(sizeof(phylib_table));
    double current_period = table->time;
    if (new_table == NULL)
    {
        printf("NEW TABLE NULL FOR COPY TABLE\n");
        return NULL;
    }
    else {
        int i = 0;
        while (i < PHYLIB_MAX_OBJECTS)
        {
            phylib_copy_object(&(new_table->object[i]), &(table->object[i]));
            i++; 
        }    
    }
    new_table->time = current_period;
    return new_table;
}

void phylib_add_object(phylib_table *table, phylib_object *object) {
    if (table == NULL || object == NULL) {
        printf("ERROR TABLE OR OBJECT ARE NULL IN ADD OBJECT\n");
        return;
    }
    int i = 0;
    while (i < PHYLIB_MAX_OBJECTS)
    {
        if (table->object[i] == NULL) {
            table->object[i] = object;
            break;
        }
        i++; 
    }
}
// Functions to free table memory
void phylib_free_table(phylib_table *table) {
    if (table == NULL) {
        printf("ERROR TABLE NULL IN FREE TABLE\n");
        return;
    }
    int i = 0;
    while (i < PHYLIB_MAX_OBJECTS)
    {
        if ((table->object)[i]) {
            free((table->object)[i]);
            (table->object)[i] = NULL;
        }
        i++; // did not increment i previously
    }
    free(table);
}

phylib_coord phylib_sub(phylib_coord c1, phylib_coord c2) {
    phylib_coord result;
    result.x = c1.x - c2.x;
    result.y = c1.y - c2.y;
    return result;
}

double phylib_length(phylib_coord c) {
    return sqrt(c.x * c.x + c.y * c.y);
}

double phylib_dot_product(phylib_coord a, phylib_coord b) {
    return a.x * b.x + a.y * b.y;
}

// Helper function to calculate the distance between two points
double phylib_distance(phylib_object *obj1, phylib_object *obj2) {
    if (obj1 == NULL || obj2 == NULL) {
        printf("OBJ 1 OR OBJ2 IS NULL\n");
        return -1.0; // Invalid input
    }

    if (obj1->type != PHYLIB_ROLLING_BALL) {
        printf("OBJ1 IS NOT OF TYPE ROLLING BALL\n");
        return -1.0; // obj1 must be a rolling ball
    }

    double distance = -1.0;

    switch(obj2->type) {
        case PHYLIB_ROLLING_BALL:
        case PHYLIB_STILL_BALL: ;
            distance = phylib_length(phylib_sub(obj1->obj.rolling_ball.pos, obj2->obj.rolling_ball.pos)) - PHYLIB_BALL_DIAMETER;
        break;
        case PHYLIB_HOLE:
            distance = phylib_length(phylib_sub(obj1->obj.rolling_ball.pos, obj2->obj.hole.pos)) - PHYLIB_HOLE_RADIUS;
        break;
        case PHYLIB_HCUSHION:
            distance = fabs(obj1->obj.rolling_ball.pos.y - obj2->obj.hcushion.y) - PHYLIB_BALL_RADIUS;
        break;
        case PHYLIB_VCUSHION:
            distance = fabs(obj1->obj.rolling_ball.pos.x - obj2->obj.vcushion.x) - PHYLIB_BALL_RADIUS;
        break;
    }
    return distance;
}  

double phylib_square(double value) {
    return value * value;
}
// Function to check direction of velocity and acceleration
void is_sign_same_as_before (phylib_object *new, phylib_object *old) {
    if (new == NULL|| old == NULL) {
        printf("NEW OR OLD NULL IN IS SIGN SAME AS BEFORE\n");
        return;
    }
    if ((new->obj.rolling_ball.vel.x < 0 && old->obj.rolling_ball.vel.x > 0) || (new->obj.rolling_ball.vel.x > 0 && old->obj.rolling_ball.vel.x < 0)) {
        new->obj.rolling_ball.vel.x = 0.0;
        new->obj.rolling_ball.acc.x = 0.0;
    }
    if ((new->obj.rolling_ball.vel.y < 0 && old->obj.rolling_ball.vel.y > 0) || (new->obj.rolling_ball.vel.y > 0 && old->obj.rolling_ball.vel.y < 0)) {
        new->obj.rolling_ball.vel.y = 0.0;
        new->obj.rolling_ball.acc.y = 0.0;
    }
}

// Function to roll a ball
void phylib_roll(phylib_object *new, phylib_object *old, double time) {
    if (new == NULL || old == NULL)
    {
        printf("NEW OR OLD NULL IN ROLL\n");
        return;
    }
    
    if (old->type == PHYLIB_ROLLING_BALL && new->type == PHYLIB_ROLLING_BALL) 
    {
        phylib_rolling_ball *new_ball = &(new->obj.rolling_ball);
        phylib_rolling_ball *old_ball = &(old->obj.rolling_ball);

        // Update position using physics equations
        new_ball->pos.x = old_ball->pos.x + old_ball->vel.x * time + 0.5 * old_ball->acc.x * phylib_square(time);
        new_ball->pos.y = old_ball->pos.y + old_ball->vel.y * time + 0.5 * old_ball->acc.y * phylib_square(time);

        // Update velocity
        new_ball->vel.x = old_ball->vel.x + old_ball->acc.x * time;
        new_ball->vel.y = old_ball->vel.y + old_ball->acc.y * time;

        // Check for sign-change
        is_sign_same_as_before(new, old);
    }
    else
    {
        printf("NEW OR OLD NOT OF TYPE ROLLING BALL\n");
    }
}

// Function to check if a ball has stopped
unsigned char phylib_stopped(phylib_object *object) {
    if (object == NULL) {
        printf("OBJECT NULL IN STOPPED\n");
        return 0;
    }
    if (object->type == PHYLIB_ROLLING_BALL) 
    {
        phylib_rolling_ball *ball = &(object->obj.rolling_ball);
        unsigned char old_number = ball->number;
        phylib_coord old_pos = ball->pos;
        // Check if the velocity is close to zero
        if (phylib_length(ball->vel) < PHYLIB_VEL_EPSILON) {
            object->type = PHYLIB_STILL_BALL;
            object->obj.still_ball.number = old_number;
            object->obj.still_ball.pos = old_pos;
            return 1;
        }
    }
    else
    {
        printf("OBJECT NOT OF TYPE ROLLING BALL IN STOPPED\n");
    }
    // Other objects are considered stopped
    return 0;
}
//Helper for division
double phylib_quotient (double divident, double divisor) {
    if (divisor != 0)
    {
        return divident/divisor;
    }
    else{
        printf("DIVISION ERROR\n");
        return 0;
    } 
}

// Function to handle bouncing of balls
void phylib_bounce(phylib_object **a, phylib_object **b) {
    if (a == NULL || b == NULL) {
        printf("A OR B NULL IN BOUNCE\n");
        goto exit;
    }
    if (*a == NULL || *b == NULL)
    {
        printf("POINTERS OF A OR B NULL IN BOUNCE\n");
        goto exit;
    }
    if ((*a)->type != PHYLIB_ROLLING_BALL) {
        printf("OBJ A NOT OF TYPE ROLLING BALL IN BOUNCE\n");  
        exit:
        return;
    }

    switch ((*b)->type)
    {
    case PHYLIB_HCUSHION:
        (*a)->obj.rolling_ball.vel.y = (-1)*(*a)->obj.rolling_ball.vel.y;
        (*a)->obj.rolling_ball.acc.y = (-1)*(*a)->obj.rolling_ball.acc.y;
        break;
    case PHYLIB_VCUSHION:
        (*a)->obj.rolling_ball.vel.x = (-1)*(*a)->obj.rolling_ball.vel.x;
        (*a)->obj.rolling_ball.acc.x = (-1)*(*a)->obj.rolling_ball.acc.x;
        break;
    case PHYLIB_HOLE:
        free(*a);
        *a = NULL;
        break;
    case PHYLIB_STILL_BALL: ;
        unsigned char number = (*b)->obj.still_ball.number;
        phylib_coord temp_pos = (*b)->obj.still_ball.pos;
        phylib_coord temp_vel = {0.0, 0.0};
        phylib_coord temp_acc = {0.0, 0.0};
        (*b)->type = PHYLIB_ROLLING_BALL;
        (*b)->obj.rolling_ball.number = number;
        (*b)->obj.rolling_ball.pos = temp_pos;
        (*b)->obj.rolling_ball.vel = temp_vel;
        (*b)->obj.rolling_ball.acc= temp_acc; 
    case PHYLIB_ROLLING_BALL: ;
        phylib_coord r_ab = phylib_sub((*a)->obj.rolling_ball.pos, (*b)->obj.rolling_ball.pos);
        phylib_coord v_rel = phylib_sub((*a)->obj.rolling_ball.vel, (*b)->obj.rolling_ball.vel);

        phylib_coord n = {0.0, 0.0};
        double len = phylib_length(r_ab); 
        n.x = phylib_quotient(r_ab.x, len);
        n.y = phylib_quotient(r_ab.y, len);

        double v_rel_n = phylib_dot_product(n, v_rel);

        (*a)->obj.rolling_ball.vel.x = (*a)->obj.rolling_ball.vel.x - (v_rel_n * n.x);
        (*a)->obj.rolling_ball.vel.y = (*a)->obj.rolling_ball.vel.y - (v_rel_n * n.y);
        
        (*b)->obj.rolling_ball.vel.x = (*b)->obj.rolling_ball.vel.x + (v_rel_n * n.x);
        (*b)->obj.rolling_ball.vel.y = (*b)->obj.rolling_ball.vel.y + (v_rel_n * n.y);
        
        double a_speed = phylib_length((*a)->obj.rolling_ball.vel);
            if (a_speed > PHYLIB_VEL_EPSILON) {
                (*a)->obj.rolling_ball.acc.x = phylib_quotient(-(*a)->obj.rolling_ball.vel.x * PHYLIB_DRAG, a_speed);
                (*a)->obj.rolling_ball.acc.y = phylib_quotient(-(*a)->obj.rolling_ball.vel.y * PHYLIB_DRAG, a_speed);
            }
        double b_speed = phylib_length((*b)->obj.rolling_ball.vel);
            if (b_speed > PHYLIB_VEL_EPSILON) {
                (*b)->obj.rolling_ball.acc.x = phylib_quotient(-(*b)->obj.rolling_ball.vel.x * PHYLIB_DRAG, b_speed);
                (*b)->obj.rolling_ball.acc.y = phylib_quotient(-(*b)->obj.rolling_ball.vel.y * PHYLIB_DRAG, b_speed);
            }
    break;
    }
}
//Returns number of rolling balls
unsigned char phylib_rolling(phylib_table *t) {
    unsigned char rolling_ball_count = 0;
    if (t == NULL) {
        printf("ERROR T IS NULL IN ROLLING\n");
        return 0;
    }
    int i = 0;
    while (i < PHYLIB_MAX_OBJECTS) {
        if ((t->object)[i] != NULL && ((t->object)[i])->type == PHYLIB_ROLLING_BALL) {
            rolling_ball_count++;
        }
        i++;
    }
    return rolling_ball_count;
}

phylib_table *phylib_segment(phylib_table *table) {
    if (table == NULL) {
        printf("ERROR TABLE IS NULL IN SEGMENT\n");
        return NULL;
    }
    phylib_table *new_table = phylib_copy_table(table);
    if (new_table == NULL) {
        printf("ERROR NEW TABLE IS NULL IN SEGMENT\n");
        return NULL;
    }
    if (phylib_rolling(new_table) == 0) {
        printf("NO ROLLING BALLS ON NEW TABLE IN SEGMENT\n");
        phylib_free_table(new_table);
        return NULL;
    }
    double time_2;
    for (double current_period = PHYLIB_SIM_RATE; current_period < PHYLIB_MAX_TIME; current_period += PHYLIB_SIM_RATE)
    {   
        for (int i = 0; i < PHYLIB_MAX_OBJECTS; i++) // loop over objects
        {
            if (new_table->object[i] != NULL && new_table->object[i]->type == PHYLIB_ROLLING_BALL)
            {
                phylib_roll(new_table->object[i], table->object[i], current_period);
            }
        }
        for(int i = 0; i < PHYLIB_MAX_OBJECTS; i++) 
        {
            if (new_table->object[i] == NULL)
            {
                continue;
            }
            if (new_table->object[i]->type == PHYLIB_ROLLING_BALL)
            {
                for (int j = 0; j < PHYLIB_MAX_OBJECTS; j++)
                { 
                    if ((new_table->object)[j] == NULL || (new_table->object)[i] == NULL || j == i)
                    {
                        continue;
                    }
                    if (phylib_distance(new_table->object[i], new_table->object[j]) < 0.0)
                    {
                        phylib_bounce(&((new_table->object)[i]), &((new_table->object)[j]));
                        new_table->time += current_period;
                        return new_table;
                    }
                }
                if (phylib_stopped((new_table->object)[i]))
                {
                    new_table->time += current_period;
                    return new_table;
                }    
            }
        }
        time_2 = current_period; 
    }
    new_table->time += time_2;
    return new_table;
}

char *phylib_object_string(phylib_object *object) {
    static char string[80];
    if (object == NULL)
    {
        snprintf(string, 80, "NULL;");
        return string;
    }
    switch (object->type)
    {
    case PHYLIB_STILL_BALL:
        snprintf(string, 80,
                 "STILL_BALL (%d,%6.1lf,%6.1lf)",
                 object->obj.still_ball.number,
                 object->obj.still_ball.pos.x,
                 object->obj.still_ball.pos.y);
        break;
    case PHYLIB_ROLLING_BALL:
        snprintf(string, 80,
                 "ROLLING_BALL (%d,%6.1lf,%6.1lf,%6.1lf,%6.1lf,%6.1lf,%6.1lf)",
                 object->obj.rolling_ball.number,
                 object->obj.rolling_ball.pos.x,
                 object->obj.rolling_ball.pos.y,
                 object->obj.rolling_ball.vel.x,
                 object->obj.rolling_ball.vel.y,
                 object->obj.rolling_ball.acc.x,
                 object->obj.rolling_ball.acc.y);
        break;
    case PHYLIB_HOLE:
        snprintf(string, 80,
                 "HOLE (%6.1lf,%6.1lf)",
                 object->obj.hole.pos.x,
                 object->obj.hole.pos.y);
        break;
    case PHYLIB_HCUSHION:
        snprintf(string, 80,
                 "HCUSHION (%6.1lf)",
                 object->obj.hcushion.y);
        break;
    case PHYLIB_VCUSHION:
        snprintf(string, 80,
                 "VCUSHION (%6.1lf)",
                 object->obj.vcushion.x);
        break;
    }
    return string;
}