<?php
// Sprawdzamy, czy dane zostały wysłane metodą POST
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // Pobieramy dane przesyłane z ESP32
    $wilgotnosc_gleby_przed = $_POST['wilgotnosc_gleby_przed'];
    $wilgotnosc_gleby_po = $_POST['wilgotnosc_gleby_po'];
    $temperatura = $_POST['temperatura'];
    $stan = $_POST['stan'];
    $godzina = $_POST['godzina'];
    $data = $_POST['data'];

    // Połączenie z bazą danych (przykład z MySQL)
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "esp_data";

    // Tworzenie połączenia
    $conn = new mysqli($servername, $username, $password, $dbname);

    // Sprawdzanie połączenia
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    // Tworzenie zapytania SQL
    $sql = "INSERT INTO sensor_data (wilgotnosc_gleby_przed, wilgotnosc_gleby_po, temperatura, stan, godzina, data)
            VALUES ('$wilgotnosc_gleby_przed', '$wilgotnosc_gleby_po', '$temperatura', '$stan', '$godzina', '$data')";

    // Wykonanie zapytania
    if ($conn->query($sql) === TRUE) {
        echo "Dane zapisane!";
    } else {
        echo "Błąd: " . $sql . "<br>" . $conn->error;
    }

    // Zamknięcie połączenia
    $conn->close();
}
?>
