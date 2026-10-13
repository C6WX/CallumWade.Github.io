# GitHub Pages & Automated Doxygen Deployment Setup

This document provides an overview of how automated builds, GitHub Actions workflows, and GitHub Pages hosting are configured for this portfolio repository.

---

## 1. How the GitHub Actions Workflow Works

The automated pipeline is defined in `.github/workflows/pages.yml`. It triggers automatically whenever new commits are pushed to the `main` branch.

### Workflow Execution Steps

1. **Trigger (`on: push`):** Listens for pushes to the `main` branch.
2. **Environment & Permissions:** Requests write permissions for GitHub Pages (`pages: write`) and security tokens (`id-token: write`).
3. **Checkout Code:** Uses `actions/checkout@v4` to retrieve the latest repository files.
4. **Install Dependencies:** Installs `doxygen` and `graphviz` on the Ubuntu runner via `apt-get`.
5. **Build Doxygen Docs:** Navigates to the `src/` directory and executes `doxygen Doxyfile`. This scans the documented C++ source code (`math_utils.cpp`) and outputs static HTML files into `docs/html/`.
6. **Prepare Payload (`_site`):**
   - Creates a temporary directory named `_site`.
   - Copies `index.html`, `education.html`, `projects.html`, and the `css/` directory into `_site/`.
   - Copies generated Doxygen HTML files into `_site/docs/html/`.
7. **Upload & Deploy Artifact:** 
   - Uses `actions/upload-pages-artifact@v3` to bundle `_site`.
   - Uses `actions/deploy-pages@v4` to publish the artifact live to GitHub Pages.

---

## 2. How GitHub Pages Is Enabled in the Repository

GitHub Pages is configured to deploy directly from the GitHub Actions workflow output rather than a static branch.

### Repository Configuration Settings

1. On GitHub.com, navigate to **Settings** > **Pages** (under *Code and automation*).
2. Under **Build and deployment** -> **Source**, select **GitHub Actions** from the dropdown menu.
3. No static branch needs to be selected manually, as `actions/deploy-pages@v4` securely handles deployment permissions using OpenID Connect (OIDC).

---

## 3. Where the Generated Docs Appear on the Live Site

Once the GitHub Action build pipeline completes, the portfolio and code documentation are live at the following endpoints:

* **Main Portfolio Website:**  
  `https://c6wx.github.io/CallumWade.Github.io/`
* **Education Page:**  
  `https://c6wx.github.io/CallumWade.Github.io/education.html`
* **Projects:**  
  `https://c6wx.github.io/CallumWade.Github.io/projects.html`
* **Automated Doxygen C++ Docs:**  
  `https://c6wx.github.io/CallumWade.Github.io/docs/html/index.html`

The navigation header across all pages links directly to `docs/html/index.html` to allow seamless browsing between portfolio projects and technical C++ API documentation.