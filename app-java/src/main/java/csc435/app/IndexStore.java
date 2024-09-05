package csc435.app;

import java.util.ArrayList;
import java.util.HashMap;

// Data structure that stores a document number and the number of time a word/term appears in the document
class DocFreqPair {
    public long documentNumber;
    public long wordFrequency;

    public DocFreqPair(long documentNumber, long wordFrequency) {
        this.documentNumber = documentNumber;
        this.wordFrequency = wordFrequency;
    }
}

public class IndexStore {
    // TO-DO declare data structure that keeps track of the DocumentMap
    // TO-DO declare data structures that keeps track of the TermInvertedIndex

    public IndexStore() {
        // TO-DO initialize the DocumentMap and TermInvertedIndex members
    }

    public long putDocument(String documentPath) {
        long documentNumber = 0;
        // TO-DO assign a unique number to the document path and return the number

        return documentNumber;
    }

    public String getDocument(long documentNumber) {
        String documentPath = "";
        // TO-DO retrieve the document path that has the given document number

        return documentPath;
    }

    public void updateIndex(long documentNumber, HashMap<String, Long> wordFrequencies) {
        // TO-DO update the TermInvertedIndex with the word frequencies of the specified document
    }

    public ArrayList<DocFreqPair> lookupIndex(String term) {
        ArrayList<DocFreqPair> results = new ArrayList<>();
        // TO-DO return the document and frequency pairs for the specified term

        return results;
    }
}
