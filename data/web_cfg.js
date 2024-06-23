
function loadDefaults() {
    if(confirm('Are you sure you want to load the default settings? Controller will restart.')) {
        fetch('/loadDefaults', { method: 'POST' })
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                location.reload();
            })
            .catch(error => {
                console.error('There has been a problem with your fetch operation:', error);
            });
    }
}


function powerCycle() {
    if(confirm('Device will restart and animations will start running again. May need to reconnect to device wifi continue configuring.')) {
        fetch('/powerCycle', { method: 'GET' })
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                location.reload();
            })
            .catch(error => {
                console.error('There has been a problem with your fetch operation:', error);
            });
    }
}

function exportConfig() {
    fetch('/export')
        .then(response => response.blob())
        .then(blob => {
            // Create a new URL for the blob
            const url = window.URL.createObjectURL(blob);
            // Create a temporary anchor element
            const a = document.createElement('a');
            // Set the href to the blob URL
            a.href = url;
            // Set the download attribute to the desired file name
            a.download = 'config.json';
            // Append the anchor to the body
            document.body.appendChild(a);
            // Trigger the download
            a.click();
            // Remove the anchor from the body
            document.body.removeChild(a);
            // Release the blob URL
            window.URL.revokeObjectURL(url);
        })
        .catch(error => console.error('Error downloading the config:', error));
}

function importConfig() {
    var fileInput = document.getElementById('importFile');
    var file = fileInput.files[0];
    if (!file) {
        alert('Please select a file before clicking "Import Config"');
        return;
    }
    var reader = new FileReader();
    reader.onload = function(e) {
        var config = JSON.parse(e.target.result);
        fetch('/import', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(config)
        })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            alert('Config imported successfully');
            location.reload();
        })
        .catch(error => {
            console.error('There has been a problem with your fetch operation:', error);
            alert('Failed to import config');
        });
    }
    reader.readAsText(file);
}

function submitFormAsJson() {
    var r = confirm("Are you sure you want to apply changes (only visible tab)? Controller will restart.");
    if (r == true) {
        var form = document.getElementById('configForm');
        var formData = new FormData(form);
        var jsonData = {};

        for (var pair of formData.entries()) {
        jsonData[pair[0]] = pair[1];
        }

        fetch(form.action, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(jsonData)
        });
    }
}

function showHideFieldSets(){
    typeValue = document.getElementById('out_type');
    if (typeValue.value == 'single') {
        document.getElementById('out_single_fields').style.display = 'block';
        document.getElementById('out_strip_fields').style.display = 'none';
    } else if (typeValue.value == 'strip') {
        document.getElementById('out_single_fields').style.display = 'none';
        document.getElementById('out_strip_fields').style.display = 'block';
    }

    document.getElementById('out_type').addEventListener('change', function() {
        if (this.value == 'single') {
            document.getElementById('out_single_fields').style.display = 'block';
            document.getElementById('out_strip_fields').style.display = 'none';
        } else if (this.value == 'strip') {
            document.getElementById('out_single_fields').style.display = 'none';
            document.getElementById('out_strip_fields').style.display = 'block';
        }
    });
}

function loadDefaultTab(){
    importButton = document.getElementById('importButton');
    if (importButton) {
        importButton.addEventListener('click', function() {
            document.getElementById('importFile').click();
        });
    }

    importFile = document.getElementById('importFile');
    if (importFile) {
        importFile.addEventListener('change', function() {
            importConfig();
        });
    }

    level1Button = document.getElementById('level1TabButton');
    firstLoadLevel = true;
    for (let i = 1; i <= 3; i++) {
        let div = document.getElementById(`level_${i}_tab`);
        if (div) {
            firstLoadLevel = false;
        }
    }

    if (level1Button && firstLoadLevel) {
        level1Button.click();
        return;
    }

    var leveltablist = document.querySelector('.leveltablist');
    if(leveltablist){
        var levelButtons = leveltablist.querySelectorAll('.leveltablinks');
        levelButtons.forEach(function(levelButton) {
            levelButton.addEventListener('click', function() {
                // Remove the 'active' class from all buttons
                levelButtons.forEach(function(btn) {
                    btn.classList.remove('active');
                });
        
                // Add the 'active' class to the clicked button
                this.classList.add('active');
            });
        });
    }

    out1Button = document.getElementById('output1TabButton');
    firstLoadOutput = true;
    for (let i = 1; i <= 12; i++) {
        let div = document.getElementById(`out_${i}_tab`);
        if (div) {
            firstLoadOutput = false;
        }
    }

    var outtablist = document.querySelector('.outtablist');
    if(outtablist){
        var outButtons = outtablist.querySelectorAll('.outtablinks');
        outButtons.forEach(function(outButton) {
            outButton.addEventListener('click', function() {
                // Remove the 'active' class from all buttons
                outButtons.forEach(function(btn) {
                    btn.classList.remove('active');
                });
        
                // Add the 'active' class to the clicked button
                this.classList.add('active');
            });
        });
    }

    if (out1Button && firstLoadOutput) {
        out1Button.click();
        return;
    }
}

window.onload = function() {

    var maintablist = document.querySelector('.maintablist');
    var mainbuttons = maintablist.querySelectorAll('.maintablinks');
    mainbuttons.forEach(function(mainButton) {
        mainButton.addEventListener('click', function() {
            // Remove the 'active' class from all buttons
            mainbuttons.forEach(function(btn) {
                btn.classList.remove('active');
            });
    
            // Add the 'active' class to the clicked button
            this.classList.add('active');
        });
    });

    document.getElementById('inputTabButton').click();
}