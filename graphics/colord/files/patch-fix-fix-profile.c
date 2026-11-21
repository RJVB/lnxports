diff --git client/cd-fix-profile.c client/cd-fix-profile.c
index 3e90e48..4c909da 100644
--- client/cd-fix-profile.c
+++ client/cd-fix-profile.c
@@ -49,6 +49,8 @@ typedef struct {
 	CdUtilPrivateCb	 callback;
 } CdUtilItem;
 
+static struct _cmsICCPROFILE *lcmsProfile = NULL;
+
 static void
 cd_util_item_free (CdUtilItem *item)
 {
@@ -285,7 +287,7 @@ cd_util_get_coverage (cmsHPROFILE profile_proof,
 
 	/* load proofing profile */
 	icc_ref = cd_icc_new ();
-	ret = cd_icc_load_handle (icc_ref, profile_proof,
+	ret = cd_icc_load_borrowed_handle (icc_ref, profile_proof,
 				  CD_ICC_LOAD_FLAGS_NONE, error);
 	if (!ret)
 		goto out;
@@ -565,10 +567,12 @@ cd_util_lcms_error_cb (cmsContext ContextID,
 	g_warning ("LCMS error %" G_GUINT32_FORMAT ": %s", errorcode, text);
 }
 
+static CdUtilPrivate *theProfile = NULL; // instead of the `priv` local in main()
+
 int
 main (int argc, char *argv[])
 {
-	CdUtilPrivate *priv;
+// 	CdUtilPrivate *theProfile;
 	gboolean ret = TRUE;
 	gboolean verbose = FALSE;
 	guint retval = 1;
@@ -594,86 +598,86 @@ main (int argc, char *argv[])
 	cmsSetLogErrorHandler (cd_util_lcms_error_cb);
 
 	/* create helper object */
-	priv = g_new0 (CdUtilPrivate, 1);
-	priv->rewrite_file = TRUE;
-	priv->client = cd_client_new ();
+	theProfile = g_new0 (CdUtilPrivate, 1);
+	theProfile->rewrite_file = TRUE;
+	theProfile->client = cd_client_new ();
 
 	/* add commands */
-	priv->cmd_array = g_ptr_array_new_with_free_func ((GDestroyNotify) cd_util_item_free);
-	cd_util_add (priv->cmd_array,
+	theProfile->cmd_array = g_ptr_array_new_with_free_func ((GDestroyNotify) cd_util_item_free);
+	cd_util_add (theProfile->cmd_array,
 		     "extract-vcgt",
 		     /* TRANSLATORS: command description */
 		     _("Generate the VCGT calibration of a given size"),
 		     cd_util_extract_vcgt);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "md-clear",
 		     /* TRANSLATORS: command description */
 		     _("Clear any metadata in the profile"),
 		     cd_util_clear_metadata);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "md-init",
 		     /* TRANSLATORS: command description */
 		     _("Initialize any metadata for the profile"),
 		     cd_util_init_metadata);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "md-add",
 		     /* TRANSLATORS: command description */
 		     _("Add a metadata item to the profile"),
 		     cd_util_add_metadata);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "md-remove",
 		     /* TRANSLATORS: command description */
 		     _("Remove a metadata item from the profile"),
 		     cd_util_remove_metadata);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "set-copyright",
 		     /* TRANSLATORS: command description */
 		     _("Sets the copyright string"),
 		     cd_util_set_copyright);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "set-description",
 		     /* TRANSLATORS: command description */
 		     _("Sets the description string"),
 		     cd_util_set_description);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "set-manufacturer",
 		     /* TRANSLATORS: command description */
 		     _("Sets the manufacturer string"),
 		     cd_util_set_manufacturer);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "set-model",
 		     /* TRANSLATORS: command description */
 		     _("Sets the model string"),
 		     cd_util_set_model);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "md-fix",
 		     /* TRANSLATORS: command description */
 		     _("Automatically fix metadata in the profile"),
 		     cd_util_set_fix_metadata);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "set-version",
 		     /* TRANSLATORS: command description */
 		     _("Set the ICC profile version"),
 		     cd_util_set_version);
-	cd_util_add (priv->cmd_array,
+	cd_util_add (theProfile->cmd_array,
 		     "export-tag-data",
 		     /* TRANSLATORS: command description */
 		     _("Export the tag data"),
 		     cd_util_export_tag_data);
 
 	/* sort by command name */
-	g_ptr_array_sort (priv->cmd_array,
+	g_ptr_array_sort (theProfile->cmd_array,
 			  (GCompareFunc) cd_sort_command_name_cb);
 
 	/* get a list of the commands */
-	priv->context = g_option_context_new (NULL);
-	cmd_descriptions = cd_util_get_descriptions (priv->cmd_array);
-	g_option_context_set_summary (priv->context, cmd_descriptions);
+	theProfile->context = g_option_context_new (NULL);
+	cmd_descriptions = cd_util_get_descriptions (theProfile->cmd_array);
+	g_option_context_set_summary (theProfile->context, cmd_descriptions);
 
 	/* TRANSLATORS: program name */
 	g_set_application_name (_("Color Management"));
-	g_option_context_add_main_entries (priv->context, options, NULL);
-	ret = g_option_context_parse (priv->context, &argc, &argv, &error);
+	g_option_context_add_main_entries (theProfile->context, options, NULL);
+	ret = g_option_context_parse (theProfile->context, &argc, &argv, &error);
 	if (!ret) {
 		/* TRANSLATORS: the user didn't read the man page */
 		g_print ("%s: %s\n", _("Failed to parse arguments"),
@@ -682,7 +686,7 @@ main (int argc, char *argv[])
 	}
 
 	/* use explicit locale */
-	priv->locale = g_strdup (locale);
+	theProfile->locale = g_strdup (locale);
 
 	/* set verbose? */
 	if (verbose) {
@@ -700,8 +704,8 @@ main (int argc, char *argv[])
 
 	/* open file */
 	file = g_file_new_for_path (argv[1]);
-	priv->icc = cd_icc_new ();
-	ret = cd_icc_load_file (priv->icc,
+	theProfile->icc = cd_icc_new ();
+	ret = cd_icc_load_file (theProfile->icc,
 				file,
 				CD_ICC_LOAD_FLAGS_ALL,
 				NULL,
@@ -710,17 +714,18 @@ main (int argc, char *argv[])
 		g_print ("%s\n", error->message);
 		goto out;
 	}
+	lcmsProfile = (struct _cmsICCPROFILE*)cd_icc_get_handle(theProfile->icc);
 
 	/* run the specified command */
-	ret = cd_util_run (priv, argv[2], (gchar**) &argv[2], &error);
+	ret = cd_util_run (theProfile, argv[2], (gchar**) &argv[2], &error);
 	if (!ret) {
 		g_print ("%s\n", error->message);
 		goto out;
 	}
 
 	/* save file */
-	if (priv->rewrite_file) {
-		ret = cd_icc_save_file (priv->icc,
+	if (theProfile->rewrite_file) {
+		ret = cd_icc_save_file (theProfile->icc,
 					file,
 					CD_ICC_SAVE_FLAGS_NONE,
 					NULL,
@@ -734,15 +739,15 @@ main (int argc, char *argv[])
 	/* success */
 	retval = 0;
 out:
-	if (priv != NULL) {
-		if (priv->cmd_array != NULL)
-			g_ptr_array_unref (priv->cmd_array);
-		g_option_context_free (priv->context);
-		if (priv->icc != NULL)
-			g_object_unref (priv->icc);
-		g_object_unref (priv->client);
-		g_free (priv->locale);
-		g_free (priv);
+	if (theProfile != NULL) {
+		if (theProfile->cmd_array != NULL)
+			g_ptr_array_unref (theProfile->cmd_array);
+		g_option_context_free (theProfile->context);
+		if (theProfile->icc != NULL)
+			g_object_unref (theProfile->icc);
+		g_object_unref (theProfile->client);
+		g_free (theProfile->locale);
+		g_free (theProfile);
 	}
 	return retval;
 }
diff --git lib/colord/cd-icc.c lib/colord/cd-icc.c
index eeba0d3..c9677b3 100644
--- lib/colord/cd-icc.c
+++ lib/colord/cd-icc.c
@@ -81,6 +81,7 @@ typedef struct
 	CdColorXYZ		 red;
 	CdColorXYZ		 green;
 	CdColorXYZ		 blue;
+	gboolean		 borrowed_lcms_profile;
 } CdIccPrivate;
 
 G_DEFINE_TYPE_WITH_PRIVATE (CdIcc, cd_icc, G_TYPE_OBJECT)
@@ -2123,6 +2124,46 @@ cd_icc_load_handle (CdIcc *icc,
 	return cd_icc_load (icc, flags, error);
 }
 
+/**
+ * cd_icc_load_borrowed_handle:
+ * @icc: a #CdIcc instance.
+ * @handle: a cmsHPROFILE instance
+ * @flags: a set of #CdIccLoadFlags
+ * @error: A #GError or %NULL
+ *
+ * Like cd_icc_load_handle(), but does NOT take ownership (adopt) @handle.
+ **/
+gboolean
+cd_icc_load_borrowed_handle (CdIcc *icc,
+		    gpointer handle,
+		    CdIccLoadFlags flags,
+		    GError **error)
+{
+	CdIccPrivate *priv = GET_PRIVATE (icc);
+	cmsContext context;
+
+	g_return_val_if_fail (CD_IS_ICC (icc), FALSE);
+	g_return_val_if_fail (handle != NULL, FALSE);
+	g_return_val_if_fail (priv->lcms_profile == NULL, FALSE);
+
+	/* check the THR version has been correctly set up */
+	context = cmsGetProfileContextID (handle);
+	if (context == NULL) {
+		// don't close the handle here!
+		g_set_error_literal (error,
+				     CD_ICC_ERROR,
+				     CD_ICC_ERROR_FAILED_TO_CREATE,
+				     "lcms2 threadsafe version (THR) not used, "
+				     "or context not set");
+		return FALSE;
+	}
+
+	/* load profile */
+	priv->lcms_profile = handle;
+	priv->borrowed_lcms_profile = TRUE;
+	return cd_icc_load (icc, flags, error);
+}
+
 /**
  * cd_icc_get_size:
  *
@@ -4103,9 +4144,10 @@ cd_icc_finalize (GObject *object)
 	g_hash_table_destroy (priv->metadata);
 	for (i = 0; i < CD_MLUC_LAST; i++)
 		g_hash_table_destroy (priv->mluc_data[i]);
-	if (priv->lcms_profile != NULL)
+	if (priv->lcms_profile != NULL && !priv->borrowed_lcms_profile) {
 		cmsCloseProfile (priv->lcms_profile);
-	cd_context_lcms_free (priv->context_lcms);
+		cd_context_lcms_free (priv->context_lcms);
+	}
 
 	G_OBJECT_CLASS (cd_icc_parent_class)->finalize (object);
 }
diff --git lib/colord/cd-icc.h lib/colord/cd-icc.h
index b6b27c5..2a43f71 100644
--- lib/colord/cd-icc.h
+++ lib/colord/cd-icc.h
@@ -153,6 +153,11 @@ gboolean	 cd_icc_load_handle			(CdIcc		*icc,
 							 CdIccLoadFlags	 flags,
 							 GError		**error)
 							 G_GNUC_WARN_UNUSED_RESULT;
+gboolean	 cd_icc_load_borrowed_handle			(CdIcc		*icc,
+							 gpointer	 handle,
+							 CdIccLoadFlags	 flags,
+							 GError		**error)
+							 G_GNUC_WARN_UNUSED_RESULT;
 GBytes		*cd_icc_save_data			(CdIcc		*icc,
 							 CdIccSaveFlags	 flags,
 							 GError		**error)
