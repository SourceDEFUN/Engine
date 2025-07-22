class CDocument {
    public:
    CDocument();
    
};

class CDocTemplate {
    public:
    CDocTemplate() {}
    virtual void AddDocument(CDocument* pDoc);
};

class CWinApp {
    public:
    CWinApp() {}
    virtual void AddDocTemplate(CDocTemplate* pDocTemplate);
};
