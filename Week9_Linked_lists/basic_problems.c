#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NgaySinh {
    int ngay, thang, nam;
} NgaySinh;

typedef struct SinhVien {
    char maSV[10];
    char hoTen[50];
    char gioiTinh[5];
    NgaySinh ngaySinh;
    char diaChi[100];
    char lop[10];
    char khoa[20];
    struct SinhVien* next;
} SinhVien;

typedef struct DanhSachSinhVien {
    SinhVien* head;
    SinhVien* tail;
} DanhSachSinhVien;

void nhapThongTinSinhVien(SinhVien* sv) {
    printf("Nhap ma sinh vien: ");
    fgets(sv->maSV, sizeof(sv->maSV), stdin);
    sv->maSV[strcspn(sv->maSV, "\n")] = '\0'; 

    printf("Nhap ho ten: ");
    fgets(sv->hoTen, sizeof(sv->hoTen), stdin);
    sv->hoTen[strcspn(sv->hoTen, "\n")] = '\0';

    printf("Nhap gioi tinh: ");
    fgets(sv->gioiTinh, sizeof(sv->gioiTinh), stdin);
    sv->gioiTinh[strcspn(sv->gioiTinh, "\n")] = '\0';

    printf("Nhap ngay sinh (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &sv->ngaySinh.ngay, &sv->ngaySinh.thang, &sv->ngaySinh.nam);
    getchar(); 

    printf("Nhap dia chi: ");
    fgets(sv->diaChi, sizeof(sv->diaChi), stdin);
    sv->diaChi[strcspn(sv->diaChi, "\n")] = '\0';

    printf("Nhap lop: ");
    fgets(sv->lop, sizeof(sv->lop), stdin);
    sv->lop[strcspn(sv->lop, "\n")] = '\0';

    printf("Nhap khoa: ");
    fgets(sv->khoa, sizeof(sv->khoa), stdin);
    sv->khoa[strcspn(sv->khoa, "\n")] = '\0';

    sv->next = NULL;
}

void themSinhVienVaoDanhSach(DanhSachSinhVien* dsSV, SinhVien* sv) {
    if (dsSV->head == NULL) {
        dsSV->head = dsSV->tail = sv;
    } else {
        dsSV->tail->next = sv;
        dsSV->tail = sv;
    }
}

DanhSachSinhVien* nhapDanhSachSinhVien() {
    DanhSachSinhVien* dsSV = (DanhSachSinhVien*)malloc(sizeof(DanhSachSinhVien));
    dsSV->head = dsSV->tail = NULL;

    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        SinhVien* sv = (SinhVien*)malloc(sizeof(SinhVien));
        nhapThongTinSinhVien(sv);
        themSinhVienVaoDanhSach(dsSV, sv);
    }

    return dsSV;
}

void sapXepDanhSachSinhVienTheoMaSV(DanhSachSinhVien* dsSV) {
    SinhVien* temp = dsSV->head;
    while (temp != NULL) {
        SinhVien* minNode = temp;
        SinhVien* r = temp->next;
        while (r != NULL) {
            if (strcmp(r->maSV, minNode->maSV) < 0) {
                minNode = r;
            }
            r = r->next;
        }
        char temp_maSV[10];
        strcpy(temp_maSV, temp->maSV);
        strcpy(temp->maSV, minNode->maSV);
        strcpy(minNode->maSV, temp_maSV);

        SinhVien* temp2 = temp->next;
        temp->next = minNode->next;
        minNode->next = temp2;

        temp = temp->next;
    }
}

void inSinhVienCungNgaySinh(DanhSachSinhVien* dsSV, NgaySinh ngaySinh) {
    SinhVien* temp = dsSV->head;
    int found = 0;
    while (temp != NULL) {
        if (temp->ngaySinh.ngay == ngaySinh.ngay && temp->ngaySinh.thang == ngaySinh.thang && temp->ngaySinh.nam == ngaySinh.nam) {
            printf("Ma SV: %s\nHo ten: %s\nGioi tinh: %s\nNgay sinh: %02d/%02d/%04d\nDia chi: %s\nLop: %s\nKhoa: %s\n\n", temp->maSV, temp->hoTen, temp->gioiTinh, temp->ngaySinh.ngay, temp->ngaySinh.thang, temp->ngaySinh.nam, temp->diaChi, temp->lop, temp->khoa);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("Khong tim thay sinh vien cung ngay sinh\n");
    }
}

void loaiBoSinhVienCungNgaySinh(DanhSachSinhVien* dsSV, NgaySinh ngaySinh) {
    SinhVien* temp = dsSV->head;
    SinhVien* prev = NULL;
    while (temp != NULL) {
        if (temp->ngaySinh.ngay == ngaySinh.ngay && temp->ngaySinh.thang == ngaySinh.thang && temp->ngaySinh.nam == ngaySinh.nam) {
            if (prev == NULL) {
                dsSV->head = temp->next;
            } else {
                prev->next = temp->next;
            }
            if (temp == dsSV->tail) {
                dsSV->tail = prev;
            }
            SinhVien* next = temp->next;
            free(temp);
            temp = next;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

int main() {
    DanhSachSinhVien* dsSV = nhapDanhSachSinhVien();
    
    SinhVien* temp = dsSV->head;
    while (temp != NULL) {
        printf("Ma SV: %s\nHo ten: %s\nGioi tinh: %s\nNgay sinh: %02d/%02d/%04d\nDia chi: %s\nLop: %s\nKhoa: %s\n\n", temp->maSV, temp->hoTen, temp->gioiTinh, temp->ngaySinh.ngay, temp->ngaySinh.thang, temp->ngaySinh.nam, temp->diaChi, temp->lop, temp->khoa);
        temp = temp->next;
    }

    NgaySinh ngaySinh;
    
    printf("Nhap ngay sinh can tim (dd/mm/yyyy): ");
    scanf("%d/%d/%d", &ngaySinh.ngay, &ngaySinh.thang, &ngaySinh.nam);
    inSinhVienCungNgaySinh(dsSV, ngaySinh);
    
    loaiBoSinhVienCungNgaySinh(dsSV, ngaySinh);
    
    temp = dsSV->head;
    while (temp != NULL) {
        printf("Ma SV: %s\nHo ten: %s\nGioi tinh: %s\nNgay sinh: %02d/%02d/%04d\nDia chi: %s\nLop: %s\nKhoa: %s\n\n", temp->maSV, temp->hoTen, temp->gioiTinh, temp->ngaySinh.ngay, temp->ngaySinh.thang, temp->ngaySinh.nam, temp->diaChi, temp->lop, temp->khoa);
        temp = temp->next;
    }

    return 0;
}