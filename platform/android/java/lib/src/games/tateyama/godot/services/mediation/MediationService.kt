package games.tateyama.godot.services.mediation
import android.content.Context
import com.google.android.gms.ads.MobileAds
import com.google.android.gms.ads.initialization.InitializationStatus
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener

class MediationService(
	private val context: Context
) {
	fun initialize() {
		MobileAds.initialize(
			context,
			{ initializationStatus: InitializationStatus -> }
		)
	}

	companion object {
		@JvmStatic
		external fun onInitializationComplete(addr: Long)
	}
}
