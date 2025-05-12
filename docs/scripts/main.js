window.addEventListener("DOMContentLoaded", () => {
  fetch("style/navbar.html")
    .then(response => {
      if (!response.ok) throw new Error("Network response was not ok");
      return response.text();
    })
    .then(html => {
      document.getElementById("IncludedNavbar").innerHTML = html;
    })
    .catch(error => {
      console.error("Error loading included content:", error);
    });
  fetch("style/sidebar.html")
    .then(response => {
      if (!response.ok) throw new Error("Network response was not ok");
      return response.text();
    })
    .then(html => {
      document.getElementById("IncludedSidebar").innerHTML = html;
    })
    .catch(error => {
      console.error("Error loading included content:", error);
    });
});
