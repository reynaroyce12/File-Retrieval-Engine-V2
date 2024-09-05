package csc435.app;

public class FileRetrievalEngine 
{
    public static void main( String[] args )
    {
        IndexStore store = new IndexStore();
        ProcessingEngine engine = new ProcessingEngine(store);
        AppInterface appInterface = new AppInterface(engine);

        appInterface.readCommands();
    }
}
