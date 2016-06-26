﻿using UnityEngine;
using System.Collections;

[ExecuteInEditMode]
public class Billboard : MonoBehaviour {
	
	// Update is called once per frame
	void Update ()
    {
        transform.LookAt(Camera.main.transform.position, -Vector3.up);
    }
}
