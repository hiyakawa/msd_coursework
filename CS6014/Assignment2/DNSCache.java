package MSDNS;

import java.util.HashMap;

public class DNSCache {
    private static HashMap<DNSQuestion, DNSRecord> cache_;

    public DNSCache() {
        cache_ = new HashMap<>();
    }

    /**
     * add a record to the question
     */
    public static void addRecord(MSDNS.DNSQuestion question, DNSRecord record) {
        cache_.put(question, record);
    }

    /**
     * get a record from the question
     */
    public static DNSRecord getRecord(MSDNS.DNSQuestion question) {
        return cache_.get(question);
    }

    /**
     * @return if cache contains the question
     */
    public static boolean contains(MSDNS.DNSQuestion question) {
        if (cache_.containsKey(question)) {
            if (! cache_.get(question).isExpired()) {
                return true;
            }

            cache_.remove(question);
        }

        return false;
    }
}
