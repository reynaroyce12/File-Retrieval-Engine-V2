package csc435.app;

import java.util.ArrayList;

class IndexResult {
    public double executionTime;
    public long totalBytesRead;

    public IndexResult(double executionTime, long totalBytesRead) {
        this.executionTime = executionTime;
        this.totalBytesRead = totalBytesRead;
    }
}

class DocPathFreqPair {
    public String documentPath;
    public long wordFrequency;

    public DocPathFreqPair(String documentPath, long wordFrequency) {
        this.documentPath = documentPath;
        this.wordFrequency = wordFrequency;
    }
}

class SearchResult {
    public double excutionTime;
    public ArrayList<DocPathFreqPair> documentFrequencies;

    public SearchResult(double executionTime, ArrayList<DocPathFreqPair> documentFrequencies) {
        this.excutionTime = executionTime;
        this.documentFrequencies = documentFrequencies;
    }
}

public class ProcessingEngine {
    // keep a reference to the index store
    private IndexStore store;
    
    // the number of worker threads to use during indexing
    private int numWorkerThreads;

    public ProcessingEngine(IndexStore store, int numWorkerThreads) {
        this.store = store;
        this.numWorkerThreads = numWorkerThreads;
    }

    public IndexResult indexFiles(String folderPath) {
        IndexResult result = new IndexResult(0.0, 0);
        // TO-DO get the start time
        // TO-DO crawl the folder path and extrac all file paths
        // TO-DO create the worker threads and give to each worker a subset of the documents that need to be indexed
        // TO-DO for each file put the document path in the index store and retrieve the document number
        // TO-DO for each file extract all alphanumeric terms that are larger than 2 characters
        //       and count their frequencies
        // TO-DO increment the total number of read bytes
        // TO-DO update the main index with the word frequencies for each document
        // TO-DO join all of the worker threads
        // TO-DO get the stop time and calculate the execution time
        // TO-DO return the execution time and the total number of bytes read

        return result;
    }
    
    public SearchResult searchFiles(ArrayList<String> terms) {
        SearchResult result = new SearchResult(0.0, new ArrayList<DocPathFreqPair>());
        // TO-DO get the start time
        // TO-DO for each term get the pairs of documents and frequencies from the index store
        // TO-DO combine the returned documents and frequencies from all of the specified terms
        // TO-DO sort the document and frequency pairs and keep only the top 10
        // TO-DO for each document number get from the index store the document path
        // TO-DO get the stop time and calculate the execution time
        // TO-DO return the execution time and the top 10 documents and frequencies

        return result;
    }
}
