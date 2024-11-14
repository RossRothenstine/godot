package games.tateyama.godot.services.mediation;

import com.google.android.gms.ads.MobileAds;
import android.content.Context;

class MediationService {
	private final Context context;
	private final long nativeHandle;

	public MediationService(Context context, long nativeHandle) {
		this.context = context;
		this.nativeHandle = nativeHandle;
	}

	public void initialize() {
		MobileAds.initialize(context, (status) -> {
			nativeInitialized(nativeHandle);
		});
	}

	private native static void nativeInitialized(long nativeHandle);
}
