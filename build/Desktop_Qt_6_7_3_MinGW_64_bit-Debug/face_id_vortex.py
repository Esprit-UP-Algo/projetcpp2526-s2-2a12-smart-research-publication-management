from flask import Flask, request, jsonify
import cv2
import numpy as np
import os

app = Flask(__name__)
face_cascade = cv2.CascadeClassifier(cv2.data.haarcascades + 'haarcascade_frontalface_default.xml')

@app.route('/health', methods=['GET'])
def health():
    return jsonify({'ok': True})

@app.route('/enroll', methods=['POST'])
def enroll():
    if 'face' in request.files:
        username = request.form.get('username', 'user')
        img = cv2.imdecode(np.frombuffer(request.files['face'].read(), np.uint8), cv2.IMREAD_COLOR)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        faces = face_cascade.detectMultiScale(gray, 1.1, 4)
        if len(faces) > 0:
            x, y, w, h = faces[0]
            face_crop = img[y:y+h, x:x+w]
            cv2.imwrite(f'{username}_ref.jpg', face_crop)
            return jsonify({'success': True})
    return jsonify({'success': False})

@app.route('/verify', methods=['POST'])
def verify():
    if 'face' in request.files:
        username = request.form.get('username', 'user')
        ref_path = f'{username}_ref.jpg'
        if not os.path.exists(ref_path): return jsonify({'verified': False})
        img_ref = cv2.imread(ref_path, 0)
        img_new = cv2.imdecode(np.frombuffer(request.files['face'].read(), np.uint8), cv2.IMREAD_GRAYSCALE)
        faces = face_cascade.detectMultiScale(img_new, 1.1, 4)
        if len(faces) > 0:
            x, y, w, h = faces[0]
            curr = cv2.resize(img_new[y:y+h, x:x+w], (img_ref.shape[1], img_ref.shape[0]))
            score = cv2.matchTemplate(curr, img_ref, cv2.TM_CCOEFF_NORMED).max()
            return jsonify({'verified': bool(score > 0.7)})
    return jsonify({'verified': False})

if __name__ == '__main__':
    app.run(host='127.0.0.1', port=5000)
