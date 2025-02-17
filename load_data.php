<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "esp_data";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$offset = isset($_GET['offset']) ? intval($_GET['offset']) : 0;
$limit = isset($_GET['limit']) ? intval($_GET['limit']) : 10;

$sql = "SELECT data, godzina, stan, wilgotnosc_gleby_przed, wilgotnosc_gleby_po, temperatura 
        FROM sensor_data 
        ORDER BY id DESC 
        LIMIT $limit OFFSET $offset";

$result = $conn->query($sql);

if ($result->num_rows > 0) {
    while ($row = $result->fetch_assoc()) {
        echo "<tr>";
        echo "<td>" . $row['data'] . "</td>";
        echo "<td>" . $row['godzina'] . "</td>";
        echo "<td>" . $row['stan'] . "</td>";
        echo "<td>" . $row['wilgotnosc_gleby_przed'] . "</td>";
        echo "<td>" . ($row['wilgotnosc_gleby_po'] !== "brak" ? $row['wilgotnosc_gleby_po'] : "-") . "</td>";
        echo "<td>" . $row['temperatura'] . "</td>";
        echo "</tr>";
    }
}

$conn->close();
?>
