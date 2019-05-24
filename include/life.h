#ifndef LIFE_H
#define LIFE_H

#include <cstdlib>  // size_t
#include <iostream> // std::cerr
#include <exception>
#include <algorithm> 
#include <string>
#include <map>
#include <sstream>
#include "canvas.h"
#include "common.h"
#include "lodepng.h"


namespace life
{

    /*! Class so that the program operates by receiving configurations
     * via command-line arguments.
    */
    class data{
        //=== Private data
    private:
            bool help; //!< Print this help text.
            std::string imgdir; //!< Specify directory where output images are written to.
            int maxgen; //!< Maximum number of generations to simulate.
            int fps; //!< Number of generations presented per second.
            int blocksize; //!< Pixel size of a cell. Default = 5.
            Color bkgcolor; //!< Color name for the background. Default GREEN.
            Color alivecolor; //!< Color name for representing alive cells. Default RED.
            std::string outfile; //!< Write the text representation of the simulation to the given filename.
            std::string filedir; //!< Specify the initial file directory for generations
        //=== Public data
        public:
            Color which_color(std::string color){
                if(color == "BLACK")
                    return BLACK;
                else if(color == "BLUE")
                    return DEEP_SKY_BLUE;
                else if(color == "CRIMSON")
                    return CRIMSON;
                else if(color == "DARK_GREEN")
                    return DARK_GREEN;
                else if(color == "DEEP_SKY_BLUE")
                    return DEEP_SKY_BLUE;
                else if(color == "DODGER_BLUE")
                    return DODGER_BLUE;
                else if(color == "GREEN")
                    return GREEN;
                else if(color == "LIGHT_BLUE")
                    return LIGHT_BLUE;
                else if(color == "LIGHT_GREY")
                    return LIGHT_GREY;
                else if(color == "LIGHT YELLOW")
                    return LIGHT_YELLOW;
                else if(color == "RED")
                    return RED;
                else if(color == "STEEL_BLUE")
                    return STEEL_BLUE;
                else if(color == "WHITE")
                    return WHITE;
                else if(color == "YELLOW")
                    return YELLOW;
                else
                {
                    std::cout << ">>> The color wasn't found.\n";
                    return this->bkgcolor;
                }
            }

            /// Constructor
            data(int argc, char *argv[]): help(false), imgdir("../gens/"), maxgen(-1), outfile("std::cout"), fps(1), filedir("0"),blocksize(30), bkgcolor(GREEN), alivecolor(RED){
                for( auto i{0}; i < argc; i++ ){
                    std::string param(argv[i]);
                    if( param == "--help" )
                    {
                        this->help = true;
                    }
                    else if( param == "--imgdir" )
                    {
                        this->imgdir = argv[i+1];
                    }
                    else if( param == "--maxgen" )
                    {
                        this->maxgen = std::atoi(argv[i+1]);
                    }
                    else if( param == "--fps" )
                    {
                        this->fps = std::atoi(argv[i+1]);
                    }
                    else if( param == "--blocksize" )
                    {
                        this->blocksize = std::atoi(argv[i+1]);
                    }
                    else if( param == "--bkgcolor" )
                    {
                        std::string color = argv[i+1];
                        this->bkgcolor = which_color(color);
                    }
                    else if( param  == "--alivecolor" )
                    {
                        std::string color = argv[i+1];
                        this->alivecolor = which_color(color);
                    }
                    else if( param  == "--outfile" )
                    {
                        this->outfile = argv[i+1];
                    }
                    else
                    {
                        this->filedir = argv[i];
                    }
                }
            };
            
            /// Destructor
            ~data(){/*vazio*/};

            /// Print the help text
            void print_help(){
                std::cout << "Usage: glife [<options>] <input_cfg_file> \n"
                << "  Simulation options: \n"
                << "     --help Print this help text.\n"
                << "     --imgdir <path> Specify directory where output images are written to. \n"
                << "     --maxgen <num> Maximum number of generations to simulate.\n"
                << "     --fps <num> Number of generations presented per second.\n"
                << "     --blocksize <num> Pixel size of a cell. Default = 5.\n"
                << "     --bkgcolor <color> Color name for the background. Default GREEN.\n"
                << "     --alivecolor <color> Color name for representing alive cells. Default RED.\n"
                << "     --outfile <filename> Write the text representation of the simulation\n"
                << "     to the given filename.\n"
                << "  Available colors are:\n"
                << "       BLACK BLUE CRIMSON DARK_GREEN DEEP_SKY_BLUE DODGER_BLUE \n"
                << "       GREEN LIGHT_BLUE LIGHT_GREY LIGHT_YELLOW RED STEEL_BLUE \n"
                << "       WHITE YELLOW \n";

            }

            /*!
            @return The help attibute.
            */
            bool get_help()
            {
                return this->help;
            }

            /*!
            @return The imgdir attribute.
            */
            std::string get_imgdir()
            {
                return this->imgdir;
            }

            /*! 
            @return The maxgen attribute.
            */
            int get_maxgen()
            {
                return this->maxgen;
            }

            /*!
            @return The fps attribute.
            */
            int get_fps()
            {
                return this->fps;
            }

            /*!
            @return The blocksize attribute.
            */
            int get_blocksize()
            {
                return this->blocksize;
            }

            /*!
            @return The bkgcolor attribute.
            */
            Color get_bkgcolor()
            {
                return this->bkgcolor;
            }

            /*!
            @return The alivecolor attribute
            */
            Color get_alivecolor()
            {
                return this->alivecolor;
            }

            /*!
            @return The outfile attribute
            */
            std::string get_outfile()
            {
                return this->outfile;
            }

            /*!
            @return The filedir attribute
            */
            std::string get_filedir()
            {
                return this->filedir;
            }

            /*! 
             * Indicate the output mode.
             @return 0, if receives just --outfile
             @return 1, if receives just --imgdir
             @return 2, if receives --outfile and --imgdir
             @return -1, otherwise
             */
            int output_mode()
            {
                if(outfile != "std::cout" && imgdir == "../gens/") return 0;
                else if(outfile == "std::cout" && imgdir != "../gens/")return 1;
                else if(outfile != "std::cout" && imgdir != "../gens/")return 2;
                else return -1;
            }

        };

        /*!
         * Class that represents one configuration in the
         * life game.
         */
        class life_game
        {
        public:
            typedef std::vector<std::vector<bool>> matriz; //!< Matrix whose elements correspond to cells that may or may not be alive.
        //=== Private data
        private:
            matriz genconfig; //!< Main matrix for cell configuration.
            matriz support;     //!< Support matrix for the generation update.
            std::map<std::string, int> check_stable; //!< Map to check the stability of the current generation with the previous generations
            char identifier;    //!< Live cell identification character.
            int num_linhas, num_colunas, key=0, generations = 0;
            std::ofstream out; //!< Stream for output file.

        //=== Public data
        public:
            /// Constructor that receives the file with the data.
            life_game(data input)
            {
                if(input.get_help())
                {
                    input.print_help();
                    std::quick_exit(1);
                }
                std::cout << "\n****************************************************************\n"
                          << "               Welcome to Conway’s game of Life.\n" 
                          << "****************************************************************\n\n";
                std::ifstream gen;
                gen.open(input.get_filedir(), std::ios::in);
                if(input.output_mode() == 0 )out.open(input.get_outfile(), std::ios::out);

                std::cout << ">>> Trying to open input file [" << input.get_filedir() << "]... ";
                if(gen.is_open() && input.get_filedir() != "0") 
                {
                    std::cout << "done!\n>>> Running simulation\n";
                    gen >> num_linhas;
                    gen >> num_colunas;
                    gen >> identifier;

                    std::vector<std::vector<char>> symbols(num_linhas+2);   // Matriz de caracteres para checar o identificador
                    genconfig.resize(num_linhas+2);                        // inicio as duas matrizes já com as linhas extras 
                    
                    symbols[0].assign(num_colunas+2, ' ');                  // Inicio as linhas iniciais para mortas.
                    genconfig[0].assign(num_colunas+2, false);

                    std::string line;

                    gen.get();
                    for(int i = 1; i<num_linhas+2; i++)
                    {
                        symbols[i].assign(num_colunas+2, ' ');               // Inicio cada linha com valores mortos
                        genconfig[i].assign(num_colunas+2, false); 
                        std::getline(gen, line); 
                        for(int j = 0; j<num_colunas; j++)
                        {
                            //gen >> symbols[i].at(j);
                            if(j >= line.size())genconfig[i].at(j+1) = false;
                            else
                            {                         
                                if(line[j] == identifier) genconfig[i].at(j+1) = true;    // Dou um set nas vivas
                            }
                        }
                        //gen.get();
                    }

                    check_stable.insert(std::pair<std::string, int>(convert_string(genconfig), key));
                    key++;

                    if(input.output_mode() == 0){
                        out << "\nGeneration: " << generations << std::endl;
                        std::cout << ">>> Updating the archive: " << input.get_outfile() << std::endl;
                        for(auto vetor: genconfig)
                        {
                            out << "[";
                            for(auto linha: vetor)
                            {
                                if(linha) out << identifier;
                                else out << " ";
                            }
                            out << "]" << std::endl;
                        }
                    }

                    if(input.output_mode() == -1 ){
                        std::cout << "\nGeneration: " << generations << std::endl;

                        for(auto vetor: genconfig)
                        {
                            std::cout << "[";
                            for(auto linha: vetor)
                            {
                                if(linha) std::cout << identifier;
                                else std::cout << " ";
                            }
                            std::cout << "]" << std::endl;
                        }

                    }
                    
                    if(input.output_mode() == 1 || input.output_mode() == 2 )
                    {
                        print_gen(name_file(generations), input);
                        std::cout << ">>> Generating image: " << "Cfg" << generations << std::endl;
                    }
                    support = genconfig;

                    generations++;
                }

                else
                {
                    std::cout << "fail(ABORTING)\n";
                    std::quick_exit(1);
                }
            }

            /// Apply the simulation rules and update the configuration.
            void update( data input ) 
            {
                int cont;
                for(int i = 1; i<num_linhas+1; i++)
                {
                    for(int j = 1; j<num_colunas+1; j++)
                    {
                        cont = 0;
                            if(genconfig[i-1].at(j-1) == true)cont++;       // Testes das células vizinhas
                            if(genconfig[i-1].at(j) == true)cont++;
                            if(genconfig[i-1].at(j+1) == true)cont++;
                            if(genconfig[i].at(j-1) == true)cont++;
                            if(genconfig[i].at(j+1) == true)cont++;
                            if(genconfig[i+1].at(j-1) == true)cont++;
                            if(genconfig[i+1].at(j) == true)cont++;
                            if(genconfig[i+1].at(j+1) == true)cont++;
                            
                            if(genconfig[i].at(j))                  
                            {
                                if(cont <= 1)support[i].at(j) = false;                  //D01  D = DIE
                                else if(cont > 1 && cont <=3)support[i].at(j) = true;   //S23  S = SURVIVE
                                else support[i].at(j) = false;                          //D45678
                            }
                            else
                            {
                                if(cont==3)support[i].at(j) = true;                     //B3   B = BORN           
                            }
                            
                        }
                    }
                    
                    genconfig = support;        // Após todas as mudanças serem carregadas na support, passo para a matriz principal

                    if(input.output_mode() == 0){
                        out << "\nGeneration: " << generations << std::endl;

                        for(auto vetor: genconfig)
                        {
                            out << "[";
                            for(auto linha: vetor)
                            {
                                if(linha) out << identifier;
                                else out << " ";
                            }
                            out << "]" << std::endl;
                        }

                    }
                    if(extinct())
                    {
                        std::cout << "EXTINCT!\n";
                        if(out.is_open())out << "EXTINCT!\n";
                    }
                    else
                    {
                        if(input.output_mode() == 1 || input.output_mode() == 2 )
                        {
                            print_gen(name_file(generations), input);
                            std::cout << ">>> Generating image: " << "Cfg" << generations << std::endl;
                        }
                        key++;

                        if(input.output_mode() == -1 ){
                            std::cout << "\nGeneration: " << generations << std::endl;

                            for(auto vetor: genconfig)
                            {
                                std::cout << "[";
                                for(auto linha: vetor)
                                {
                                    if(linha) std::cout << identifier;
                                    else std::cout << " ";
                                }
                                std::cout << "]" << std::endl;
                            }

                        }
                    }
                    generations++;
                }

                /// Indicates if a configuration is extinguished.
                bool extinct()
                {
                    bool check_extinct = false;
                    for(int i = 1; i<num_linhas+1; i++)
                    {
                        for(int j = 1; j<num_colunas+1; j++)
                        {
                            if(genconfig[i].at(j) == true) check_extinct = true;
                        }
                    }
                    return !check_extinct;
                }

            /// Create the png file
            void encode_png(std::string filename, const unsigned char * image, unsigned width, unsigned height)
            {
                //Encode the image
                unsigned error = lodepng::encode(filename, image, width, height);

                //if there's an error, display it
                if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
            }

            /// Generate the png image according to the current generation
            void print_gen(std::string file, data colors) 
            {
                unsigned width = num_linhas, height = num_colunas;
                //short block_size = colors.get_blocksize();
                Canvas image(height, width, colors.get_blocksize() );           
                for(int i = 1; i<num_linhas+1; i++)
                {
                    for(int j = 1; j<num_colunas+1; j++)
                    {
                        if(genconfig[i].at(j)) image.pixel( Point2(j-1,i-1) , colors.get_alivecolor() );
                        else image.pixel( Point2(j-1,i-1) , colors.get_bkgcolor() );
                    }
                }


                //save_ppm3( image.pixels(), image.width(), image.height(), 4, colors.get_imgdir() + file);
                encode_png(colors.get_imgdir() + file, image.pixels(), image.width(), image.height() );
            }

            /// Indicates whether a configuration is stable.
            bool stable()
            {
                auto check = check_stable.find(convert_string(genconfig));
                if(check != check_stable.end())
                {
                    std::cout << "STABLE! The generation " << (key - 1) << " is equal to the generation " << (check->second)-1 << "!\n";
                    if(out.is_open())out << "STABLE (With the generation: " << (check->second)-1 << ")!\n";

                  return true;
                }
                else
                {
                    check_stable.insert(std::pair<std::string, int>(convert_string(genconfig), key));
                    return false;
                }
            }

            /// Convert the matrix into a string to use on the map
            std::string convert_string(matriz atual)
            {
                std::string retorno;
                for(int i = 1; i<num_linhas+1; i++)
                {
                    for(int j = 1; j<num_colunas+1; j++)
                    {
                        if(atual[i].at(j))
                        {
                            retorno += '1';
                        }

                        else
                        {
                            retorno += '0';
                        } 
                    }

                }
                return retorno;
            }

        /// Return the name of the image file
        std::string name_file(int number_gen)
        {
            std::ostringstream buffer; //tratando uma string como uma stream
            buffer << "Cfg" << number_gen << ".png";

            return buffer.str();    
        }
    };

}

#endif
