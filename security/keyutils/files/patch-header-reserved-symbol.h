diff --git b/orig.keyutils.h a/keyutils.h
index 887cbf2..e7269e0 100644
--- b/keyutils.h
+++ a/keyutils.h
@@ -218,7 +218,7 @@ extern long keyctl_invalidate(key_serial_t id);
 extern long keyctl_get_persistent(uid_t uid, key_serial_t id);
 extern long keyctl_dh_compute(key_serial_t priv, key_serial_t prime,
 			      key_serial_t base, char *buffer, size_t buflen);
-extern long keyctl_dh_compute_kdf(key_serial_t private, key_serial_t prime,
+extern long keyctl_dh_compute_kdf(key_serial_t privkey, key_serial_t prime,
 				  key_serial_t base, char *hashname,
 				  char *otherinfo, size_t otherinfolen,
 				  char *buffer, size_t buflen);
