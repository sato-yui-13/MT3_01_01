#include <Novice.h>
#include <Vector3.h>
#include <Matrix.h>
#include <WinApp.h>

const char kWindowTitle[] = "LE2D_13_サトウ_ユイ_MT3_01_01";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 v1{ 1.2f,-3.9f,2.5f };
	Vector3 v2{ 2.8f,0.4f,-1.3f };

	Vector3 rotate{};
	Vector3 translate{};

	int kWindowWidth = 1280;
	int kWindowHeight = 720;

	Vector3 cameraPosition{ 0, 0, -300.0f };

	const Vector3 kRectSize = { 50,50 };


	// 正三角形の定義に使う辺の長さ（kRectSize.xを使う）
	const float sideLength = kRectSize.x;
	// 正三角形の高さ h = √3 / 2 * 辺の長さ
	const float triangleHeight = sqrtf(3.0f) / 2.0f * sideLength;


	//指定が無いので矩形の中心は(0,0)で良い
	Vector3 rectCenter = { 0, 0 };

	const Vector3 kLocalVertices[3] =
	{
	   { -sideLength / 2.0f, -triangleHeight / 3.0f, 0.0f },  // 左下
	   {  sideLength / 2.0f, -triangleHeight / 3.0f, 0.0f },  // 右下
	   {  0.0f, 2.0f * triangleHeight / 3.0f, 0.0f }   // 上
	};

	const float moveSpeed = 2.0f;
	const float rotateSpeed = 0.05f;


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Vector3 cross = Cross(v1, v2);

		if (keys[DIK_W]) {
			translate.y += moveSpeed;
		}
		if (keys[DIK_S]) {
			translate.y -= moveSpeed;
		}
		if (keys[DIK_A]) {
			translate.x -= moveSpeed;
		}
		if (keys[DIK_D]) {
			translate.x += moveSpeed;
		}

		rotate.y += rotateSpeed;

		//各種行列の計算
		Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
		Vector3  screenVertices[3];
		for (uint32_t i = 0; i < 3; i++)
		{
			Vector3 ndcVectex = Transform(kLocalVertices[i], worldViewProjectionMatrix);
			screenVertices[i] = Transform(ndcVectex, viewportMatrix);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		VectorScreenPrintf(0, 0, cross, "Cross");

		Novice::DrawTriangle(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y),
			int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
