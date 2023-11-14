
package com.$safeprojectname$;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;

public class $safeprojectname$ extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        /* Create a TextView and set its text to "PGE Mobile 2.2.2" */
        TextView  tv = new TextView(this);
        tv.setText("OLC PGE Mobile 2.2.2");
        setContentView(tv);
    }
}
