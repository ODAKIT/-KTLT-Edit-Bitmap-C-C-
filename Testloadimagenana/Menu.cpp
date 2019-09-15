#include"Menu.h"
#include<Windows.h>
#include<algorithm>
#include"ProcessImage.h"
#include<iostream>



using namespace std;
void Menu()
{
	//Các kiểu dữ liệu cần thiết để thực hiện chương trình
	BitMap _header;
	char*_data = NULL;
	char *backdata = NULL;


	//sử dụng thư viện nana.
	using namespace nana;
	//Tạo một window mang tên fm.
	form fm{ API::make_center(600, 600) };
	form inputstring;	

	// Dùng để mở rộng cửa sổ	
	fm.div("vert <> < weight=283 <><pic weight=283><> > <>");

	// Picture dùng để load
	// Image dùng để xử lý
	nana::paint::image a;


	// Biến đếm click ( đếm số lần click chẵn lẽ) dùng để ẩn hoặc hiện các slider - ảnh ...
	int demclick = 0;




	// Tạo một menu dùng để load ảnh từ các file do người dùng chọn
	menubar mnbar(fm);
	mnbar.push_back("Load image");
	filebox fb(true);
	char *file = new char[100];
	nana::drawing dw(fm);
	//Event click vào menu 
	mnbar.events().click([&]
	{
		demclick = 0;
	
		fb.add_filter("All Files", "*.bmp*");
		string fileop;
		if (fb()) //When user clicked 'OK'
		{
			fileop = fb.file();
		}
		for (int i = 0; i < fileop.length(); i++)
		{
			file[i] = fileop[i];
		}
		file[fileop.length()] = NULL;
		//Chọn file xong ( chọn theo tên ) thì đọc file
		readBMP(file, _header, _data);
		readBMP(file, _header, backdata);

		//xuất ảnh ra
		a.open(file);
		dw.draw([&](nana::paint::graphics & graph)
		{

			a.paste(graph, nana::point{ 120,80 });

		});
		dw.update();

	});



	//===========Đây sẽ là chức khoanh vùng ảnh đề chỉnh sửa ==============
	// Mousex , mousey là chọn tọa độ tại vị trí click chuột
	int mousex, mousey;
	int checkdraw = 0;
	//Draw choose
	nana::drawing areachoose{ fm };
	fm.events().dbl_click([&](const arg_mouse& arg) {
		checkdraw = 1;
		areachoose.draw([&](nana::paint::graphics & grp)
		{
			grp.line({ arg.pos.x, arg.pos.y }, { arg.pos.x - 200 , arg.pos.y }, colors::black);
			grp.line({ arg.pos.x - 200, arg.pos.y }, { arg.pos.x - 200 , arg.pos.y - 200 }, colors::black);
			grp.line({ arg.pos.x - 200, arg.pos.y - 200 }, { arg.pos.x , arg.pos.y - 200 }, colors::black);
			grp.line({ arg.pos.x , arg.pos.y - 200 }, { arg.pos.x  , arg.pos.y }, colors::black);
			mousex = arg.pos.x - 200 - 120;
			mousey = _header.m_height - arg.pos.y + 80;
		});
		areachoose.update();


	});








	fm.caption(L"Photostupid - Do An 2 KTLT");   // Tên cửa sổ.








	//=============Create Button============
	// Tham số thứ 1 - 2 : tọa độ button , tham số 3 - 4 độ dài - rộng của button
	//Button ảnh trắng đen
	button Grayscale(fm, rectangle{ 0, 60, 100, 30 });
	Grayscale.caption(L"Grayscale");
	//Button xoay ảnh
	button Rt(fm, rectangle{ 0,90,100,30 });
	Rt.caption(L"Rotate horizontally");
	//Button tăng độ sáng
	button brightness(fm, rectangle{ 0,120,100,30 });
	brightness.caption(L"Brightness");
	//Button blur ảnh
	button Blur(fm, rectangle{ 0,150,100,30 });
	Blur.caption(L"Blur");
	//Button sharpen ( nét ảnh )
	button Sharpen(fm, rectangle{ 0,180,100,30 });
	Sharpen.caption(L"Sharpen");
	//Button Emboss tăng độ tương phản
	button Emboss(fm, rectangle{ 0,210,100,30 });
	Emboss.caption(L"Emboss");
	//Button cancel ( không save )
	button cancel(fm, rectangle{ 330,0,100,30 });
	cancel.caption(L"Cancel");
	//button save
	button save(fm, rectangle{ 430,0,100,30 });
	save.caption(L"Save");
	button RBG(fm, rectangle{ 0,240,100,30 });
	RBG.caption(L"Color balance");
	button Mandel(fm, rectangle{ 0,270,100,30 });
	Mandel.caption(L"Mandelprot");
	button Twirl(fm, rectangle{ 0,300,100,30 });
	Twirl.caption(L"Twirl");
	button Sepia(fm, rectangle{0, 330, 100, 30});
	Sepia.caption(L"Sepia");
	button Neonoir(fm, rectangle{ 0,360,100,30 });
	Neonoir.caption(L"Neonoir");
	button Constrast(fm, rectangle{ 0,390,100,30 });
	Constrast.caption(L"Constrast");
	
	/*button Test(fm,rectangle{})*/
		// END CREARE BUTTON	







	//=============Create Slider(thanh kéo)============
	//Các thanh kéo chỉnh sửa theo ý thích
	nana::slider brightness_sl{ fm, { 0, 0, 300, 20 } };
	brightness_sl.hide();
	nana::slider blur_sl{ fm, {0, 0, 300, 20} };
	blur_sl.hide();
	slider sl_red{ fm, {0, 400, 300, 20} };
	sl_red.scheme().color_bar = colors::red;
	sl_red.hide();
	slider sl_blue{ fm, {0, 420, 300, 20} };
	sl_blue.scheme().color_bar = colors::blue;
	sl_blue.hide();
	slider sl_green{ fm, {0, 440, 300, 20} };
	sl_green.scheme().color_bar = colors::green;
	sl_green.hide();
	slider sl_constrast(fm, { 0,0,300,20 });
	sl_constrast.hide();
	slider sl_constrastplus(fm, { 0,30,300,20 });
	sl_constrastplus.hide();
	//END Slider




	
	// ==============CLICK VAO BUTTON SAVE ANH ================
	save.events().click([&]
	{
		brightness_sl.hide();
		blur_sl.hide();
		backdata = _data;
		writeBMP(BMP_SAVE, _header, _data);
		demclick++;
	});
	cancel.events().click([&]
	{
		brightness_sl.hide();
		blur_sl.hide();
		sl_red.hide();
		sl_blue.hide();
		sl_green.hide();
		sl_constrast.hide();
		sl_constrastplus.hide();
		_data = backdata;
		writeBMP(BMP_SAVE, _header, backdata);
		a.open(BMP_SAVE);

		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();
	});

	int demBright = 0; //Bien dem xuat hien thanh slider cua bright
	int demBlur = 0; //Bien diem so lan xuat hien cua thanh slider Blur.
	int DemRBG = 0;
	int demConstrast = 0; // Dem so lan click vao button constrast de hide - show.


	// ========================= PHẦN CHỨC NĂNG ===================

	/* Mọi chức năng đều tuân thủ theo quy trình xử lý :
	B1 : Đọc ảnh lấy số liệu
	B2 : Chuyển về mảng các pixels
	B3 : Xử lý trên các pixels đó
	B4 : chuyển các pixel đó về data
	B5 : Ghi data đó ra thành một bức ảnh
	B6 : Xuất ảnh đó ra window


	Chức năng grayscale dưới là một ví dụ các chức năng sau là tương tự
	*/
	//===============Chuc nang anh trang den===============
	// Envent click vào button
	Grayscale.events().click([&]
	{
		//Bước 1 : đọc hình ảnh
		if (demclick == 0)
			readBMP(file, _header, _data);
		else
			readBMP(BMP_SAVE, _header, _data);
		//Bước 2 : Chuyển về mảng pixels
		Pix* pixels = convertDataToPixelArray(_data, _header);
		delete[] _data;
		_data = NULL;
		backdata = convertPixelArrayToData(pixels, _header);

		//Bước 3 : xử lý trên các pixels đó
		if (checkdraw == 1)
		{
			grayscaleArea(pixels, mousex, mousey, _header);
			checkdraw = 0;
		}

		else
			grayscale(pixels, _header.m_width*_header.m_height);

		_data = NULL;
		//Bước 4 : chuyển các pixels về data
		_data = convertPixelArrayToData(pixels, _header);

		//Bước 5 : ghi data ra một bức ảnh
		writeBMP(BMP_OUT, _header, _data);
		delete[] pixels;
		pixels = NULL;

		//Bước 6 : xuất bức ảnh đó ra window
		a.open(BMP_OUT);

		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();

	});





	//===============Chuc nang Dao anh doc===============
	Rt.events().click([&]
	{
		//readBMP(file, _header, _data);

		Pix* pixels = convertDataToPixelArray(_data, _header);
		delete[] _data;
		_data = NULL;
		backdata = convertPixelArrayToData(pixels, _header);

		if (checkdraw == 1)
		{
			DaoAnhDocArea(pixels, mousex, mousey, _header);
			checkdraw = 0;
		}

		else
			DaoAnhDoc(pixels, _header.m_width * _header.m_height);
		//DaoAnhDoc(pixels, _header.m_width*_header.m_height);
		_data = convertPixelArrayToData(pixels, _header); \

			writeBMP(BMP_OUT, _header, _data);
		pixels = NULL;

		a.open(BMP_OUT);
		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();

	});





	/*===============Chuc nang Brightness===============
	 Chinh sua do sang bang thanh cuon ngang.*/
	brightness.events().click([&]
	{
		//Tat ca cac thanh cuon ngang phai duoc dong lai het.
		blur_sl.hide();
		demBright++;

		brightness_sl.maximum(255);

		if (demBright % 2 != 0)
			brightness_sl.show();
		else
			brightness_sl.hide();

		brightness_sl.events().mouse_move([&]
		{

			if (brightness_sl.value() < 50)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				_data = convertPixelArrayToData(pixels, _header); \

					writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;

			}

			if (brightness_sl.value() > 50 && brightness_sl.value() < 150)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;

				Birghtness(pixels, _header);

				_data = convertPixelArrayToData(pixels, _header);

				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;

			}
			else if (brightness_sl.value() >= 150)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;

				Birghtness2(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header); \

					writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}
			// a.open , a.load duoc ho tro boi thu vien Nana de load 1 tam anh da xu ly len.
			a.open(BMP_OUT);
			nana::drawing dw(fm);
			dw.draw([&](nana::paint::graphics & graph)
			{
				a.paste(graph, nana::point{ 120,80 });
			});
			dw.update();
		});



	});

	//============CHUC NANG BLUR===============
	//Day la bien de tao vung nho tam cho data xu ly nhieu` lan theo thanh cuon ngang(Blur)
	char **ArrayData = new char *[5];
	for (int i = 0; i < 5; i++)
		ArrayData[i] = new char[5];

	//Lam mo` anh bang thanh cuong ngang.
	Blur.events().click([&]
	{

		//Show anh 
		if (demclick == 0)
			readBMP(file, _header, _data);
		else
			readBMP(BMP_SAVE, _header, _data);

		Pix* _pixels = convertDataToPixelArray(_data, _header);
		backdata = convertPixelArrayToData(_pixels, _header);

		delete[] _data;
		_data = NULL;
		_data = convertPixelArrayToData(_pixels, _header);

		writeBMP(BMP_OUT, _header, _data);
		delete[] _pixels;
		_pixels = NULL;


		// a.open , a.load duoc ho tro boi thu vien Nana de load 1 tam anh da xu ly len.
		a.open(BMP_OUT);
		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();
		//

		blur_sl.maximum(255);
		demBlur++;
		if (demBlur % 2 != 0)
		{
			blur_sl.show();
		}
		else
			blur_sl.hide();

		blur_sl.events().mouse_move([&]
		{
			if (blur_sl.value() > 50 && blur_sl.value() < 100)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);

				_pixels = convertDataToPixelArray(_data, _header);
				delete[] _data;
				_data = NULL;


				BlurImage(_pixels, _header);

				_data = convertPixelArrayToData(_pixels, _header);
				ArrayData[0] = _data;
				writeBMP(BMP_OUT, _header, ArrayData[0]);
				//Show anh
				a.open(BMP_OUT);
				nana::drawing dw(fm);
				dw.draw([&](nana::paint::graphics & graph)
				{
					a.paste(graph, nana::point{ 120,80 });
				});
				dw.update();
			}
			else if (blur_sl.value() >= 100 && blur_sl.value() < 150)
			{

				_pixels = convertDataToPixelArray(ArrayData[0], _header);
				BlurImage(_pixels, _header);
				_data = convertPixelArrayToData(_pixels, _header);
				ArrayData[1] = _data;
				writeBMP(BMP_OUT, _header, ArrayData[1]);
				delete[] _pixels;
				_pixels = NULL;
				//Show anh
				a.open(BMP_OUT);
				nana::drawing dw(fm);
				dw.draw([&](nana::paint::graphics & graph)
				{
					a.paste(graph, nana::point{ 120,80 });
				});
				dw.update();
			}
			else if (blur_sl.value() >= 150 && blur_sl.value() < 200)
			{
				_pixels = convertDataToPixelArray(ArrayData[1], _header);

				BlurImage(_pixels, _header);


				_data = convertPixelArrayToData(_pixels, _header);
				ArrayData[2] = _data;
				writeBMP(BMP_OUT, _header, ArrayData[2]);
				delete[] _pixels;
				_pixels = NULL;
				//Show anh
				a.open(BMP_OUT);
				nana::drawing dw(fm);
				dw.draw([&](nana::paint::graphics & graph)
				{
					a.paste(graph, nana::point{ 120,80 });
				});
				dw.update();
			}
			else if (blur_sl.value() >= 200)
			{

				{
					_pixels = convertDataToPixelArray(ArrayData[2], _header);

					BlurImage(_pixels, _header);


					_data = convertPixelArrayToData(_pixels, _header);
					ArrayData[3] = _data;
					writeBMP(BMP_OUT, _header, ArrayData[3]);
					delete[] _pixels;
					_pixels = NULL;
					//show anh
					a.open(BMP_OUT);
					nana::drawing dw(fm);
					dw.draw([&](nana::paint::graphics & graph)
					{
						a.paste(graph, nana::point{ 120,80 });
					});
					dw.update();
				}
			}
		});



	});


	//===============Chuc nang Sharpen===============
	//Sharpen : làm nét ảnh
	Sharpen.events().click([&]
	{
		if (demclick == 0)
			readBMP(file, _header, _data);
		else
			readBMP(BMP_SAVE, _header, _data);

		Pix* _pixels = convertDataToPixelArray(_data, _header);
		delete[] _data;
		_data = NULL;

		//Bitmap sharpenImage = new Bitmap(img.Width, img.Height);
		double filter[3][3] = { {0,-1,0}, {-1,5,-1}, {0,-1,0} };
		ProcessImageWithFilter(_pixels, filter, _header);





		_data = convertPixelArrayToData(_pixels, _header);
		writeBMP(BMP_OUT, _header, _data);
		delete[] _pixels;
		_pixels = NULL;
		a.open(BMP_OUT);
		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();
	});


	//===============Chuc nang Emboss===============
	//Emboss tang do tuong phan
	Emboss.events().click([&]
	{
		if (demclick == 0)
			readBMP(file, _header, _data);
		else
			readBMP(BMP_SAVE, _header, _data);

		Pix* _pixels = convertDataToPixelArray(_data, _header);
		delete[] _data;
		_data = NULL;


		double filter[3][3] = { {-1, -1, -1}, { -1,9,-1 }, { -1,-1,-1 } };
		ProcessImageWithFilter(_pixels, filter, _header);


		_data = convertPixelArrayToData(_pixels, _header);
		writeBMP(BMP_OUT, _header, _data);
		delete[] _pixels;
		_pixels = NULL;
		a.open(BMP_OUT);
		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();
	});


	//===============Chuc nang crop:cat anh============
	RBG.events().click([&]
	{
		blur_sl.hide();
		brightness_sl.hide();
		DemRBG++;

		sl_red.maximum(255);
		sl_blue.maximum(255);

		sl_green.maximum(255);


		if (DemRBG % 2 != 0)
		{
			sl_blue.show();
			sl_red.show();
			sl_green.show();
		}
		else
		{

			sl_blue.hide();
			sl_red.hide();
			sl_green.hide();
		}
		sl_red.events().mouse_move([&]
		{
			if (sl_red.value() > 50 && sl_red.value() < 100)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;
				editRedColorLevel1(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}
			else if (sl_red.value() >= 100 && sl_red.value() < 180)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;
				editRedColorLevel2(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}
			else if (sl_red.value() >= 180 && sl_red.value() < 256)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;
				editRedColorLevel3(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}

			a.open(BMP_OUT);
			nana::drawing dw(fm);
			dw.draw([&](nana::paint::graphics & graph)
			{
				a.paste(graph, nana::point{ 120,80 });
			});
			dw.update();

		});
		sl_blue.events().mouse_move([&]
		{
			if (sl_blue.value() > 50 && sl_blue.value() < 100)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;
				editBlueColorLevel1(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}
			else if (sl_blue.value() >= 100 && sl_blue.value() < 180)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;
				editBlueColorLevel2(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}
			else if (sl_blue.value() >= 180 && sl_blue.value() < 256)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;
				editBlueColorLevel3(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}
			a.open(BMP_OUT);
			nana::drawing dw(fm);
			dw.draw([&](nana::paint::graphics & graph)
			{
				a.paste(graph, nana::point{ 120,80 });
			});
			dw.update();

		});
		sl_green.events().mouse_move([&]
		{
			if (sl_green.value() > 50 && sl_green.value() < 100)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;
				editGreenColorLevel3(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}
			else if (sl_green.value() >= 100 && sl_green.value() < 180)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;
				editGreenColorLevel3(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}
			else if (sl_green.value() >= 180 && sl_green.value() < 256)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* pixels = convertDataToPixelArray(_data, _header);
				backdata = convertPixelArrayToData(pixels, _header);

				delete[] _data;
				_data = NULL;
				editGreenColorLevel3(pixels, _header);
				_data = convertPixelArrayToData(pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				pixels = NULL;
			}

			a.open(BMP_OUT);
			nana::drawing dw(fm);
			dw.draw([&](nana::paint::graphics & graph)
			{
				a.paste(graph, nana::point{ 120,80 });
			});
			dw.update();
		});





	});
	//Sau khi xử lý xong thì show button ra

	//=================MandelProt : chèn nét vẽ (do người lập trình vẽ)===============
	Mandel.events().click([&]
	{
		if (demclick == 0)
			readBMP(file, _header, _data);
		else
			readBMP(BMP_SAVE, _header, _data);

		Pix* _pixels = convertDataToPixelArray(_data, _header);
		delete[] _data;
		_data = NULL;

		//Bitmap sharpenImage = new Bitmap(img.Width, img.Height);
		Mandelprot(_pixels, _header);

		_data = convertPixelArrayToData(_pixels, _header);
		writeBMP(BMP_OUT, _header, _data);
		delete[] _pixels;
		_pixels = NULL;
		a.open(BMP_OUT);
		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();
	});

	//=================Twirl : Chuc nang xoáy hình ảnh==============
	Twirl.events().click([&]
	{
		if (demclick == 0)
			readBMP(file, _header, _data);
		else
			readBMP(BMP_SAVE, _header, _data);

		Pix* _pixels = convertDataToPixelArray(_data, _header);
		delete[] _data;
		_data = NULL;

		//Bitmap sharpenImage = new Bitmap(img.Width, img.Height);
		twirl(_pixels, _header);

		_data = convertPixelArrayToData(_pixels, _header);
		writeBMP(BMP_OUT, _header, _data);
		delete[] _pixels;
		_pixels = NULL;
		a.open(BMP_OUT);
		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();
	});

	//==================Sepia : chức năng ám vàng hình ảnh==========

	Sepia.events().click([&]
	{

		if (demclick == 0)
			readBMP(file, _header, _data);
		else
			readBMP(BMP_SAVE, _header, _data);

		Pix* _pixels = convertDataToPixelArray(_data, _header);
		delete[] _data;
		_data = NULL;

		//Bitmap sharpenImage = new Bitmap(img.Width, img.Height);
		sepiaConvert(_pixels, _header);

		_data = convertPixelArrayToData(_pixels, _header);
		writeBMP(BMP_OUT, _header, _data);
		delete[] _pixels;
		_pixels = NULL;
		a.open(BMP_OUT);
		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();
	});

	//==================Neonoir : 
	Neonoir.events().click([&]
	{

		if (demclick == 0)
			readBMP(file, _header, _data);
		else
			readBMP(BMP_SAVE, _header, _data);

		Pix* _pixels = convertDataToPixelArray(_data, _header);
		delete[] _data;
		_data = NULL;

		//Bitmap sharpenImage = new Bitmap(img.Width, img.Height);
		neonoir(_pixels, _header);

		_data = convertPixelArrayToData(_pixels, _header);
		writeBMP(BMP_OUT, _header, _data);
		delete[] _pixels;
		_pixels = NULL;
		a.open(BMP_OUT);
		nana::drawing dw(fm);
		dw.draw([&](nana::paint::graphics & graph)
		{
			a.paste(graph, nana::point{ 120,80 });
		});
		dw.update();

	});

	//==================Constrast : chức năng
	Constrast.events().click([&]
	{
	

		

		//Bitmap sharpenImage = new Bitmap(img.Width, img.Height);
		sl_constrast.maximum(255);
		sl_constrastplus.maximum(255);

		demConstrast++;
		if (demConstrast % 2 != 0)
		{
			sl_constrast.show();
			sl_constrastplus.show();
		}
		else
		{
			sl_constrast.hide();
			sl_constrastplus.hide();
		}
		// Tăng constrast
		sl_constrast.events().mouse_move([&]
		{
			if (sl_constrast.value() > 50 && sl_constrast.value() < 100)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* _pixels = convertDataToPixelArray(_data, _header);
				delete[] _data;
				_data = NULL;



				constrast(_pixels, _header.m_width*_header.m_height, 50);

				_data = convertPixelArrayToData(_pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				//Show anh
				a.open(BMP_OUT);
				nana::drawing dw(fm);
				dw.draw([&](nana::paint::graphics & graph)
				{
					a.paste(graph, nana::point{ 120,80 });
				});
				dw.update();
			}
			else if (sl_constrast.value() >= 100 && sl_constrast.value() < 150)
			{

				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* _pixels = convertDataToPixelArray(_data, _header);
				delete[] _data;
				_data = NULL;



				constrast(_pixels, _header.m_width*_header.m_height, 65);

				_data = convertPixelArrayToData(_pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				//Show anh
				a.open(BMP_OUT);
				nana::drawing dw(fm);
				dw.draw([&](nana::paint::graphics & graph)
				{
					a.paste(graph, nana::point{ 120,80 });
				});
				dw.update();
			}
			else if (sl_constrast.value() >= 150 && sl_constrast.value() < 200)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* _pixels = convertDataToPixelArray(_data, _header);
				delete[] _data;
				_data = NULL;



				constrast(_pixels, _header.m_width*_header.m_height, 80);

				_data = convertPixelArrayToData(_pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				//Show anh
				a.open(BMP_OUT);
				nana::drawing dw(fm);
				dw.draw([&](nana::paint::graphics & graph)
				{
					a.paste(graph, nana::point{ 120,80 });
				});
				dw.update();
			}
			else if (sl_constrast.value() >= 200)
			{

				{
					if (demclick == 0)
						readBMP(file, _header, _data);
					else
						readBMP(BMP_SAVE, _header, _data);
					Pix* _pixels = convertDataToPixelArray(_data, _header);
					delete[] _data;
					_data = NULL;



					constrast(_pixels, _header.m_width*_header.m_height, 90);

					_data = convertPixelArrayToData(_pixels, _header);
					writeBMP(BMP_OUT, _header, _data);
					//Show anh
					a.open(BMP_OUT);
					nana::drawing dw(fm);
					dw.draw([&](nana::paint::graphics & graph)
					{
						a.paste(graph, nana::point{ 120,80 });
					});
					dw.update();
				}
			}
		});

		//Giam constrast
		sl_constrastplus.events().mouse_move([&]
		{
			if (sl_constrastplus.value() > 50 && sl_constrastplus.value() < 100)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* _pixels = convertDataToPixelArray(_data, _header);
				delete[] _data;
				_data = NULL;



				constrast(_pixels, _header.m_width*_header.m_height, -10);

				_data = convertPixelArrayToData(_pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				//Show anh
				a.open(BMP_OUT);
				nana::drawing dw(fm);
				dw.draw([&](nana::paint::graphics & graph)
				{
					a.paste(graph, nana::point{ 120,80 });
				});
				dw.update();
			}
			else if (sl_constrastplus.value() >= 100 && sl_constrastplus.value() < 150)
			{

				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* _pixels = convertDataToPixelArray(_data, _header);
				delete[] _data;
				_data = NULL;



				constrast(_pixels, _header.m_width*_header.m_height, -20);

				_data = convertPixelArrayToData(_pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				//Show anh
				a.open(BMP_OUT);
				nana::drawing dw(fm);
				dw.draw([&](nana::paint::graphics & graph)
				{
					a.paste(graph, nana::point{ 120,80 });
				});
				dw.update();
			}
			else if (sl_constrastplus.value() >= 150 && sl_constrastplus.value() < 200)
			{
				if (demclick == 0)
					readBMP(file, _header, _data);
				else
					readBMP(BMP_SAVE, _header, _data);
				Pix* _pixels = convertDataToPixelArray(_data, _header);
				delete[] _data;
				_data = NULL;



				constrast(_pixels, _header.m_width*_header.m_height, -30);

				_data = convertPixelArrayToData(_pixels, _header);
				writeBMP(BMP_OUT, _header, _data);
				//Show anh
				a.open(BMP_OUT);
				nana::drawing dw(fm);
				dw.draw([&](nana::paint::graphics & graph)
				{
					a.paste(graph, nana::point{ 120,80 });
				});
				dw.update();
			}
			else if (sl_constrastplus.value() >= 200)
			{

				{
					if (demclick == 0)
						readBMP(file, _header, _data);
					else
						readBMP(BMP_SAVE, _header, _data);
					Pix* _pixels = convertDataToPixelArray(_data, _header);
					delete[] _data;
					_data = NULL;



					constrast(_pixels, _header.m_width*_header.m_height, -40);

					_data = convertPixelArrayToData(_pixels, _header);
					writeBMP(BMP_OUT, _header, _data);
					//Show anh
					a.open(BMP_OUT);
					nana::drawing dw(fm);
					dw.draw([&](nana::paint::graphics & graph)
					{
						a.paste(graph, nana::point{ 120,80 });
					});
					dw.update();
				}
			}
		});

		
	});
	fm.collocate();
	fm.show();

	exec();

}