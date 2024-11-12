import com.google.android.gms.ads.MobileAds
import android.content.Context

class MediationService(private val context: Context) {
	fun init() {
		MobileAds.initialize(context) {}
	}
}
