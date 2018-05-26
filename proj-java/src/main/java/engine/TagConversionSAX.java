import org.xml.sax.Attributes;

import java.util.HashMap;
import java.util.Map;

public class TagConversionSAX extends SAXStackOverflow {
    private Map<String,Tag> tags;

    public TagConversionSAX(){
        super();
        this.tags = new HashMap<String,Tag>();
    }

    public Map<String,Tag> getTag () {
        return this.tags;
    }

    public void rowInspector( Attributes atts){
        Long id = Long.valueOf(atts.getValue("Id"));
        String tagname = atts.getValue("TagName");
        this.tags.put(tagname,new Tag(id,tagname));
    }
}
