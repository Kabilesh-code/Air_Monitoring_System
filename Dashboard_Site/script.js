document.getElementById("loginForm").addEventListener("submit", function(event) {
    event.preventDefault();
    
    var username = document.getElementById("username").value;
    var password = document.getElementById("password").value;
    
    // Validate username and password
    if (username === "Live" && password === "Air Monitor") {
      document.getElementById("loginMessage").textContent = "Login successful!";
      document.getElementById("loginForm").reset();
      
      // Redirect to dashboard page
      window.location.href = "dashboard.html"; // Change to your actual dashboard page URL
    } else {
      document.getElementById("loginMessage").textContent = "Invalid username or password. Please try again.";
    }
  });
  