<!DOCTYPE html>
<html lang="pl">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Roślinny Asystent</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f0f9f4;
            color: #2c5f2d;
        }

        header {
            background-color: #2c5f2d;
            color: white;
            text-align: center;
            padding: 20px 10px;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
        }

        header h1 {
            margin: 0;
            font-size: 2.5rem;
        }

        .description {
            margin: 20px auto;
            max-width: 800px;
            text-align: center;
            padding: 10px;
            background-color: #dff0e2;
            border: 1px solid #a4d3a3;
            border-radius: 8px;
        }

        .description p {
            font-size: 1.1rem;
            margin: 10px 0;
        }

        .table-container {
            width: 90%;
            margin: 20px auto;
            max-height: 400px;
            overflow-y: scroll;
            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            border-radius: 8px;
            background-color: white;
        }

        table {
            border-collapse: collapse;
            width: 100%;
            background-color: white;
        }

        th, td {
            border: 1px solid #ddd;
            padding: 12px;
            text-align: center;
        }

        th {
            background-color: #a4d3a3;
            color: #2c5f2d;
        }

        tr:nth-child(even) {
            background-color: #f9f9f9;
        }

        tr:hover {
            background-color: #e6f5e6;
        }

        footer {
            text-align: center;
            padding: 10px;
            background-color: #2c5f2d;
            color: white;
            position: fixed;
            bottom: 0;
            width: 100%;
        }
    </style>
</head>
<body>
    <header>
        <h1>Roślinny Asystent</h1>
    </header>

    <div class="description">
        <p>Witaj w aplikacji <strong>Roślinny Asystent</strong>, stworzonej do monitorowania wilgotności gleby i automatycznego podlewania roślin!</p>
        <p>Obserwuj najnowsze dane pomiarowe w czasie rzeczywistym i dbaj o swoje rośliny w prosty sposób.</p>
    </div>

    <h2 style="text-align: center;">Ostatnie pomiary</h2>
    <div class="table-container">
        <table id="data-table">
            <thead>
                <tr>
                    <th>Data</th>
                    <th>Godzina</th>
                    <th>Stan</th>
                    <th>Wilgotność gleby przed podlaniem [%]</th>
                    <th>Wilgotność gleby po podlaniu [%]</th>
                    <th>Temperatura w pomieszczeniu [°C]</th>
                </tr>
            </thead>
            <tbody>
                <!-- Dane będą ładowane dynamicznie -->
            </tbody>
        </table>
    </div>

    <footer>
        <p>&copy; 2025 Roślinny Asystent. Wszystkie prawa zastrzeżone.</p>
    </footer>

    <script>
        let offset = 0;
        const limit = 10;
        const tableBody = document.querySelector('#data-table tbody');
        const tableContainer = document.querySelector('.table-container');

        function loadData() {
            fetch(`load_data.php?offset=${offset}&limit=${limit}`)
                .then(response => response.text())
                .then(data => {
                    if (data.trim() !== '') {
                        tableBody.innerHTML += data;
                        offset += limit;
                    }
                });
        }

        tableContainer.addEventListener('scroll', () => {
            if (tableContainer.scrollTop + tableContainer.clientHeight >= tableContainer.scrollHeight) {
                loadData();
            }
        });

        // Pierwsze załadowanie danych
        loadData();
    </script>
</body>
</html>
