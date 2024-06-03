#include <onnxruntime/core/session/onnxruntime_cxx_api.h>
#include <iostream>
#include <vector>

class XGBoostPredictor {
public:
    XGBoostPredictor(const char* model_path) {
        Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "XGBoostPredictor");
        session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);
        session = Ort::Session(env, model_path, session_options);
    }

    std::vector<float> predict(const std::vector<float>& input) {
        Ort::AllocatorWithDefaultOptions allocator;

        size_t input_node_count = session.GetInputCount();
        size_t output_node_count = session.GetOutputCount();

        // Vérification du nombre de nœuds d'entrée et de sortie
        if (input_node_count != 1 || output_node_count != 1) {
            throw std::runtime_error("Le modèle doit avoir exactement un nœud d'entrée et un nœud de sortie.");
        }

        // Récupération des informations sur le nœud d'entrée
        Ort::TypeInfo input_type_info = session.GetInputTypeInfo(0);
        auto input_tensor_info = input_type_info.GetTensorTypeAndShapeInfo();
        std::vector<int64_t> input_shape = input_tensor_info.GetShape();
        size_t input_size = 1;
        for (size_t i = 0; i < input_shape.size(); ++i) {
            input_size *= input_shape[i];
        }

        // Vérification de la taille du vecteur d'entrée
        if (input.size() != input_size) {
            throw std::runtime_error("La taille du vecteur d'entrée ne correspond pas à la forme attendue par le modèle.");
        }

        // Création du tableau d'entrée pour le modèle
        std::vector<float> input_buffer(input_size);
        std::copy(input.begin(), input.end(), input_buffer.begin());

        // Création du tableau de sortie pour stocker les prédictions du modèle
        std::vector<float> output_buffer;

        // Création des objets OrtValue pour les entrées et les sorties
        Ort::Value input_tensor = Ort::Value::CreateTensor<float>(allocator, input_buffer.data(), input_buffer.size(), input_shape.data(), input_shape.size());
        std::vector<Ort::Value> output_tensors = session.Run(Ort::RunOptions{ nullptr }, &input_tensor, 1, &output_node_name, 1);

        // Récupération des prédictions à partir du tableau de sortie
        auto output_tensor = output_tensors.front().GetTensorMutableData<float>();
        output_buffer.assign(output_tensor, output_tensor + output_tensors.front().GetTensorTypeAndShapeInfo().GetElementCount());

        return output_buffer;
    }

private:
    Ort::Session session;
    Ort::SessionOptions session_options;
    const char* output_node_name = "output"; // Le nom du nœud de sortie du modèle
};

int main() {
    const char* model_path = "chemin/vers/le/modele.xgboost.onnx";

    // Création d'une instance de XGBoostPredictor
    XGBoostPredictor predictor(model_path);

    // Vecteur d'entrée pour la prédiction
    std::vector<float> input = {1.0, 2.0, 3.0, 4.0}; // Exemple de vecteur d'entrée

    // Faire la prédiction
    std::vector<float> predictions = predictor.predict(input);

    // Afficher les prédictions
    std::cout << "Prédictions : ";
    for (float prediction : predictions) {
        std::cout << prediction << " ";
    }
    std::cout << std::endl;

    return 0;
}
