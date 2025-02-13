#include "console_gui.hpp"



int main(int argc, char** argv)
{
    return 0;
}


std::string getUserInputAndConvertToJson()
{
    double x, y, theta;

    try
    {
        

        // Demander à l'utilisateur d'entrer les données de position 2D
        std::cout << "Entrez la position x : ";
        if (!(std::cin >> x)) throw std::invalid_argument("Entrée invalide pour x");

        std::cout << "Entrez la position y : ";
        if (!(std::cin >> y)) throw std::invalid_argument("Entrée invalide pour y");

        std::cout << "Entrez l'angle theta : ";
        if (!(std::cin >> theta)) throw std::invalid_argument("Entrée invalide pour theta");

        
        
        // Créer un objet JSON et y ajouter les données
        nlohmann::json j;
        j["x"] = x;
        j["y"] = y;
        j["z"] = theta;

        // Convertir l'objet JSON en chaîne de caractères
        std::string json_str = j.dump();

        return json_str;
    }
    catch (const std::invalid_argument& e)
    {
        
        std::cerr << "Erreur : " << e.what() << std::endl;
        
        return "{ERROR: invalid_argument}";
    }catch (const std::runtime_error& e)
    {
        
        std::cerr << "Runtime error: " << e.what() << std::endl;
        
        ROS_INFO("console gui module, Runtime error: %s", e.what());
        return "{ERROR: runtime_error}"; 
        
    }catch(const std::exception& e)
    {
        
        std::cerr << "Exception: " << e.what() << std::endl;
        
        ROS_INFO("fusion pose data module, Exception error: %s", e.what());
        return "{ERROR: Exception_error}";  
        
    }
}
