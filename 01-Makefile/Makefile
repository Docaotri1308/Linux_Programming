.PHONY: all 

LIB_NAME	:= tris

CUR_DIR 	:= .
BIN_DIR 	:= $(CUR_DIR)/bin
INC_DIR 	:= $(CUR_DIR)/inc
OBJ_DIR 	:= $(CUR_DIR)/obj
SRC_DIR 	:= $(CUR_DIR)/src

LIB_DIR 	:= $(CUR_DIR)/lib
LIB_STATIC_DIR 	:= $(LIB_DIR)/static
LIB_SHARED_DIR 	:= $(LIB_DIR)/shared

INC_FLAGS	:= -I $(INC_DIR)

CC 		:= gcc

mk_obj_static:
	$(CC) -c $(CUR_DIR)/main.c   -o $(OBJ_DIR)/main.o   $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/hello.c  -o $(OBJ_DIR)/hello.o  $(INC_FLAGS)
	$(CC) -c $(SRC_DIR)/mymath.c -o $(OBJ_DIR)/mymath.o $(INC_FLAGS)
	 
mk_obj_shared:
	$(CC) -c -fPIC $(CUR_DIR)/main.c   -o $(OBJ_DIR)/main.o   $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/hello.c  -o $(OBJ_DIR)/hello.o  $(INC_FLAGS)
	$(CC) -c -fPIC $(SRC_DIR)/mymath.c -o $(OBJ_DIR)/mymath.o $(INC_FLAGS)

# Create the static lib
static:
	ar rcs $(LIB_STATIC_DIR)/libtris.a $(OBJ_DIR)/hello.o $(OBJ_DIR)/mymath.o

# Create the shared lib
shared:
	$(CC) -shared $(OBJ_DIR)/hello.o $(OBJ_DIR)/mymath.o -o $(LIB_SHARED_DIR)/lib$(LIB_NAME).so

install_shared:
	cp -f $(LIB_SHARED_DIR)/lib$(LIB_NAME).so /usr/lib 

all: mk_obj_static static mk_obj_shared shared install_shared
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -l$(LIB_NAME) -o $(BIN_DIR)/use-static-library
	$(CC) $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -l$(LIB_NAME) -o $(BIN_DIR)/use-shared-library

clean:
	rm -rf $(OBJ_DIR)/*
	rm -rf $(LIB_SHARED_DIR)/*
	rm -rf $(LIB_STATIC_DIR)/*
	rm -rf $(BIN_DIR)/*
